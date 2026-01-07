Solo's AnyHandle Library
========================

# Introduction

**Solo's AnyHandle** is a small C++ header-only library providing the `any_handle` class,
a safe single container for type-erased pointers.

`any_handle` is a ready-to-use replacement for standard's `any` everywhere your `any` object
is assumed to contain values of type `std::shared_ptr<T>` only.
Typically, it can be used as a building-block elment for *heterogeneous* containers.

# Motivation

- Let's note `any[T]` an object of type `std::any` whose value has type `T`. 
  Then `any_handle` is aimed to be a replacement for `any[std::shared_ptr<T>]` objects.

# Rationale

- Mimic the wording of `std::any` as much as possible.
- Keep inlined definitions as simple as possible: no assertions, no logging, no macroed throwing, etc.
- Exclude templatized definitions in the class declaration file.
- Define templatized building and casting operations outside the class declaration file.
- Packed as a header-only library.
  It is planed to provide configuration features to deliver the library as a Windows dynamic library.

## The mutability issue

- The user should be able to retrieve a mutable pointer from a handle built with a mutable `std::shared_ptr<T>`.
  This is done by storing a mutable `std::shared_ptr<void>`.
- On the other hand, the user should not be able to retrieve a mutable pointer from a handle built with
  a *non mutable* `std::shared_ptr<const T>`. So, we have to check the mutability of the type-erased pointer
  in the `mutable_pointer` method.
- But `typeid` operator ignores the const-qualifier of the type. Hence `typeid(T)` is the same as
  `typeid(const T)`. For this reason, we need to store an additional mutability flag.
- Then comes a new issue: storing a `std::type_index` member for the c++ runtime type information plus
  a boolean member for the mutablity flag will fatten the size of `any_handle` class by
  2 x `sizeof(void*)` bytes, due to the alignment with the shared pointer member. And we don't want that.
  
  We want to keep the size of the class equal to `sizeof(std::shared_ptr<void>) + sizeof(std::type_index)`.
  So we need to replace the `std::type_index` candidate member with some object of the same size that points to
  a new static type information object, where the new type information contains the `std::type_index` member and
  the mutability flag. This is the role of the `any_type_index` companion class.

## The emptiness issue

- As a container, the `any_handle` class needs to track its empty state.
- We cannot use the `void` type to mark an `any_handle` object as empty (as it is done in `std::any` class) 
  because we want the user to be able to store and retrieve valid type-erased `std::shared_ptr<void>` pointers.
- Consequently, we use again the `any_type_index` runtime type information class to store a boolean flag to mark `any_handle` objects as `empty`.

# Usages
## Basic usages
- Basic usage #1:
    - Show trivial cases. 
```
// given some advanced type...
struct A {
    int data{};
    A(int n) : data{n} {};
};
//...handled by mutable pointer and shared...
auto x = std::make_shared<A>(1);// or std::make_shared<A const>(1)
assert(x.use_count() == 1);
//...hide the pointed type in an any_handle wrapper...
auto y = solo::make_any_handle(x);// keep a _copy_ of x
static_assert(std::is_same<decltype(y),solo::any_handle>::value);
assert(x.use_count() == 2);
assert(y.pointer() == x);
assert(y.type() == typeid(A));
//...and carry it to another place where its concrete type is known...
auto rz = solo::any_handle_cast<A>(y);// or solo::any_handle_cast<A const>(y)
//...then cast it to retrieve the typed shared pointer object...
assert(rz.has_value());
auto const &z = rz.assume_value();
static_assert(std::is_same<std::decay_t<decltype(z)>,std::shared_ptr<A const>>::value);
assert(x.use_count() == 3);
assert(z == x);
```
- Basic usage #2:
    - Show how to use any_handle with a typed-erased resources container.
```
//...given an abstract resource type...
class ResourceInterface {
public : 
    virtual ~ResourceInterface() = default;
    virtual void doWork() const = 0;
};
//...given a concrete resource type implementing the resource interface...
class ConcreteResource : public ResourceInterface {
public : 
    void doWork() const override { std::cout << "working..." << std::endl; };
};
//...given a shared type-erased resources container called "register"...
auto reg = std::map<std::string,solo::any_handle>{};
{
    //...create a shared pointer on a concrete resource...
    auto x = std::make_shared<ConcreteResource>();// or std::make_shared<ConcreteResource const>()
    //...and register it as an abstract resource shared pointer...
    reg["my_resource"] = solo::make_any_handle<ResourceInterface>(x);
}
{
    //...retrieve the resource from the shared register in another place...
    auto const &ah = reg["my_resource"];
    //...we know that "my_resource" is of type "ResourceInterface", so we can cast it the the registred type...
    auto ri = solo::any_handle_cast<ResourceInterface>(ah).assume_move_value();// return std::shared_pr<ResourceInterface const>
    ri->doWork();
}
{
    //...but the handle of "my_resource" resource does not know the concrete type of the resource...
    try
    {
        auto const &rh = reg["my_resource"];
        auto ri = solo::any_handle_cast_or_throw<ConcreteResource>(rh);// throw a bad cast exception (should have cast to ResourceInterface)
    }
    catch (solo::anys::exceptions::bad_any_handle_cast const &ex)
    {
        using solo::testing::operator<<;
        std::cout << ex << std::endl;
    }
}
```
- Basic usage #3:
    - An alternative of basic usage #2 with both mutable and non-mutable resources, and generic register's getters.
```
class RxInterface {
public : 
    virtual ~RxInterface() = default;
    virtual void doX() const = 0;// non-mutable method
};
class MyResourceX : public RxInterface {
public : 
    void doX() const override { ... };
};
class RyInterface {
public : 
    virtual ~RyInterface() = default;
    virtual void doY() const = 0;// non-mutable method
    virtual void doMutable() = 0;// mutable method
};
class MyResourceY : public RyInterface {
public : 
    void doY() const override { ... };
    void doMutable() override { ... };
};
using resource_registery_type = std::map<std::string,solo::any_handle>;
template < typename RI > decltype(auto) get(resource_registery_type const &reg, std::string_view const &key) 
{ 
    return solo::any_handle_cast_or_throw<RI>(reg[key]);// return a std::shared_pr<RI const> object
}
template < typename RI > decltype(auto) get_mutable(resource_registery_type const &reg, std::string_view const &key) 
{ 
    return solo::any_handle_mutable_cast_or_throw<RI>(reg[key]);// return a std::shared_pr<RI> object
}
static auto reg = resource_registery_type{};
{
    auto x = std::make_shared<MyResourceX const>(...);
    reg["my_x"] = solo::make_any_handle<RxInterface const>(x);// non-mutable resource
    auto y = std::make_shared<MyResourceY>(...);
    reg["my_y"] = solo::make_any_handle_mutable<RyInterface>(y);// mutable resource
}
{
    auto rx = get<RxInterface const>(reg, "my_x");// or get<RxInterface>...
    rx->doX();
}
{
    auto ry = get<RyInterface const>(reg, "my_y");// or get<RyInterface>...
    ry->doY();
    auto ry_m = get_mutable<RyInterface>(reg, "my_y");// must not be get<RyInterface const>
    ry_m->doMutable();
}
```

# Reference
```
solo::any_handle
solo::any_type_index
solo::make_any_handle
solo::make_any_handle_mutable
solo::any_handle_cast
solo::any_handle_mutable_cast
solo::any_handle_cast_or_throw
solo::any_handle_mutable_cast_or_throw
solo::anys::outcomes::any_handle_cast_result
solo::anys::errors::any_handle_cast_error
solo::anys::exceptions::bad_any_handle_cast
solo::testing::operator<<
solo::boost_test_print_type
```

# Dependencies

- The whole library compiles with C++14 and C++17.
- The core library (`any_handle_core_package.h`) depends only on STL.
- The complete library (`any_handle_package.h`) contains the core library and some advanced components that depend on 
  Boost (Boost.HOF, Boost.Core and Boost.Test) and _stdex_ libraries.
- The tests suite uses the Boost.Test framework (including the Boost.Core components).

_stdex_ is another header-only library which provides C++17 features that are not available yet in C++14.
See [here](../Stdex/StdexIndex.md).

# Building
(...TODO...)

(...Up to now, the library is header-only and does not require it own building...)

(...Test suites are design for Qt Creator and build from pro files...)

# Version
See [here](../../Include/Solo/Core/Any/Handle/any_handle_library_version.h).
