//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------

#include "any_handle_testsuite_types.hpp"

// already included in make_any_handle: #include <solo/anys/handles/any_handle.hpp>
// already included in any_handle_boost_test_outputters: #include <solo/anys/handles/any_handle_cast.hpp>
#include <solo/anys/handles/make_any_handle.hpp>

#include <solo/anys/handles/testing/printing/any_handle_boost_test_outputters.hpp>
#include <stdex/testing/printing/typeindex/std_type_index_boost_test_outputters.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/function.hpp>
#include <boost/bind/bind.hpp>
#include <functional>

#include <boost/test/unit_test.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace tests {
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( SoloAnyHandleTestSuite )

//..............................................................................

inline double TestFunction(double x) { return 2 * x + 3; };

template < typename R, typename... Args >
struct InvokerInterface
{
    virtual ~InvokerInterface() = default;
    virtual R invoke(Args &&...) const = 0;
};

template < typename R, typename... Args >
struct MyInvoker: InvokerInterface<R, Args...>
{
    MyInvoker( const void *self_, R (*fptr_)(const void*, Args&&... args))
        : self(self_), fptr(fptr_)
    {}

    const void *self;
    R (*fptr)(const void *, Args&&... args);

    R invoke(Args &&... args) const override
    {
        return (*fptr)(self, std::forward<Args>(args)... );
    }
};

//..............................................................................

BOOST_AUTO_TEST_CASE( CustomDeleterTest_01 )
{
    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;

    TestObject x{1};
    auto x_deleted = false;
    {
        auto x_sh = std::shared_ptr<TestObject>(&x, [&](void *){x_deleted = true;});
        BOOST_TEST(x_sh.use_count() == 1);
        BOOST_TEST(x_deleted == false);
        {
            auto a_sh = make_any_handle(x_sh);
            BOOST_TEST(x_sh.use_count() == 2);
            BOOST_TEST(x_deleted == false);
            auto b_sh = a_sh;
            BOOST_TEST(x_sh.use_count() == 3);
            BOOST_TEST(x_deleted == false);

            auto y_sh = any_handle_cast_or_throw<TestObject>(a_sh);
            BOOST_TEST(x_sh.use_count() == 4);
            BOOST_TEST(x_deleted == false);
        }
        BOOST_TEST(x_sh.use_count() == 1);
        BOOST_TEST(x_deleted == false);
    }
    BOOST_TEST(x_deleted == true);
    BOOST_TEST(x.data() == 1);
}

BOOST_AUTO_TEST_CASE( CustomDeleterTest_02 )
{
    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;

    TestObject x{0};
    auto x_hold = [](void *self) {
        auto *x_ptr = reinterpret_cast<TestObject*>(self);
        x_ptr->setdata(x_ptr->data()+1);
    };
    auto x_release = [](void *self) {
        auto *x_ptr = reinterpret_cast<TestObject*>(self);
        x_ptr->setdata(x_ptr->data()-1);
    };
    auto make_test_handle = [&](TestObject &x) {
        x_hold(static_cast<void*>(&x));
        return std::shared_ptr<TestObject>(&x, [&](void *p){x_release(p);});
    };

    {
        auto x_sh = make_test_handle(x);
        BOOST_TEST(x_sh.use_count() == 1);
        BOOST_TEST(x_sh->data() == 1);
        {
            auto a_sh = make_any_handle<TestObject>(x_sh);
            BOOST_TEST(x_sh.use_count() == 2);
            BOOST_TEST(x_sh->data() == 1);
            auto b_sh = a_sh;
            BOOST_TEST(x_sh.use_count() == 3);
            BOOST_TEST(x_sh->data() == 1);

            auto y_sh = any_handle_cast_or_throw<TestObject>(a_sh);
            BOOST_TEST(x_sh.use_count() == 4);
            BOOST_TEST(x_sh->data() == 1);
        }
        BOOST_TEST(x_sh.use_count() == 1);
        BOOST_TEST(x_sh->data() == 1);
    }
    BOOST_TEST(x.data() == 0);
}

BOOST_AUTO_TEST_CASE( FunctionTest_01 )
{
    // try to store a function's pointer in an any_handle

    // storing a fonction's pointer in a shared pointer is allowed:
    auto f_ptr = std::shared_ptr<double(double)>(&TestFunction, [](double(*)(double)){});
    boost::ignore_unused(f_ptr);
    //DONT COMPILE:
    //auto ah = make_any_handle(f_ptr);
    // --> FAILS BECAUSE static_cast<double(*)(double)>((void*)nullptr) is not allowed

    //BOOST_TEST(ah.type() == typeid(double(double)));
    //BOOST_TEST(ah.pointer() == f_ptr);
    //auto g_ptr = any_handle_cast_or_throw<double(double)>(ah);
    //BOOST_TEST(g_ptr == f_ptr);
    //auto result = (*g_ptr)(1);
    //BOOST_TEST( result == 5 );
}

BOOST_AUTO_TEST_CASE( FunctionTest_02 )
{
    // try to store a std::function object in an any_handle

    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;

    auto callback = [=](double x) { return 2 * x + 3; };
    using function_type = std::function<double(double)>;
    auto f = function_type{callback};
    auto f_ptr = std::make_shared<function_type>(f);
    auto ah = make_any_handle(f_ptr);
    BOOST_TEST(ah.type() == typeid(function_type));
    BOOST_TEST(ah.is_mutable() == false);
    BOOST_TEST(ah.pointer() == f_ptr);
    auto g_ptr = any_handle_cast_or_throw<function_type>(ah);
    BOOST_TEST(g_ptr== f_ptr);
    auto result = (*g_ptr)(1);
    BOOST_TEST( result == 5 );
}

BOOST_AUTO_TEST_CASE( FunctionTest_03 )
{
    // a variant of the previous std::function test

    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;

    struct data_t
    {
        int a{2};
        int b{3};
    };
    const data_t data{};
    auto callback = [](const void *self, double x) -> double
    {
        auto data_ptr = reinterpret_cast<const data_t *>(self);
        return data_ptr->a * x + data_ptr->b;
    };
    using function_type = std::function<double(double)>;
    function_type f{ std::bind(callback, static_cast<const void*>(&data), std::placeholders::_1) };
    auto f_ptr = std::make_shared<function_type>(f);
    auto ah = make_any_handle(f_ptr);
    BOOST_TEST(ah.type() == typeid(function_type));
    BOOST_TEST(ah.pointer() == f_ptr);
    auto g_ptr = any_handle_cast_or_throw<function_type>(ah);
    BOOST_TEST(g_ptr == f_ptr);
    auto result = (*g_ptr)(1);
    BOOST_TEST( result == data.a+data.b );
}

BOOST_AUTO_TEST_CASE( FunctionTest_04 )
{
    // try to store the customized functor InvokerInterface<R,Args...>

    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;

    struct data_t
    {
        int a{2};
        int b{3};
    };
    const data_t data{};
    auto callback = [](const void *self, double const &x) {
        auto data_ptr = reinterpret_cast<const data_t *>(self);
        return data_ptr->a * x + data_ptr->b;
    };
    using InvokerInterfaceType = InvokerInterface<double, double const &>;
    auto f_ptr = std::make_shared< const MyInvoker<double, double const &> >(&data, callback);
    auto ah = make_any_handle<InvokerInterfaceType>(f_ptr);
    BOOST_TEST(ah.type() == typeid(InvokerInterfaceType));
    BOOST_TEST(ah.pointer() == f_ptr);
    auto h_ptr = any_handle_cast_or_throw<InvokerInterfaceType>(ah);
    BOOST_TEST(h_ptr == f_ptr);
    auto result = h_ptr->invoke(1);
    BOOST_TEST( result == data.a+data.b );
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
}}// EONS SOLOTESTS
////////////////////////////////////////////////////////////////////////////////
