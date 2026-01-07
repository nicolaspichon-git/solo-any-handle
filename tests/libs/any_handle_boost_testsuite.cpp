//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------

#include "any_handle_testsuite_types.hpp"

#include <solo/anys/handles/any_handle_core_package.hpp>
#include <solo/anys/handles/testing/printing/any_handle_boost_test_outputters.hpp>
#include <stdex/testing/printing/typeindex/std_type_index_boost_test_outputters.hpp>

#include <boost/test/unit_test.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace tests {
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( SoloAnyHandleTestSuite )

//..............................................................................

/// @brief Expose the protected constructor of <c>any_handle</c>.
class any_handle_ex: public solo::any_handle
{
public:

    explicit any_handle_ex
        (
            any_handle::internal_type_index_type const &in_ti,
            any_handle::mutable_pointer_type const &in_pointer ) noexcept
        : any_handle{ in_ti, in_pointer }
    {}

    explicit any_handle_ex
        (
            any_handle::internal_type_index_type const &in_ti,
            any_handle::mutable_pointer_type &&inout_pointer ) noexcept
        : any_handle{ in_ti, std::move(inout_pointer) }
    {}
};

//..............................................................................

BOOST_AUTO_TEST_SUITE( StdTdPreliminaryTests )

BOOST_AUTO_TEST_CASE( StdTypeidValueIgnoresCvQualifier )
{
    // -- check that standard `typeid` operator's value ignores cv qualifiers.
    BOOST_TEST(( typeid(TestObject) == typeid(const TestObject) ));
    BOOST_TEST(( typeid(TestObject) == typeid(volatile TestObject) ));
    BOOST_TEST(( typeid(TestObject) == typeid(const volatile TestObject) ));
}

BOOST_AUTO_TEST_CASE( StdSharedPtrEqOperatorComparesPointerValues )
{
    // -- check that std::shared_ptr's equality operator compares pointer values.

    auto x_sh = std::make_shared<TestObject>();
    auto y_sh = std::static_pointer_cast<const void>(x_sh);
    BOOST_TEST( y_sh == x_sh );

    // ... std::shared_ptr's equality operator does not compare to raw pointer.
    //BOOST_TEST(( x_sh == x_sh.get() ));
}

BOOST_AUTO_TEST_CASE( StdSharedPtrEqOperatorComparesToStdNullptr )
{
    // -- check that std::shared_ptr's equality operator compares to nullptr.

    auto x_sh = std::make_shared<TestObject>();
    BOOST_TEST( x_sh != nullptr );
}

BOOST_AUTO_TEST_CASE( StdSharedPtrEqOperatorIgnoresConstQualifier )
{
    auto x_sh = std::make_shared<TestObject>();
    auto y_sh = std::static_pointer_cast<const void>(x_sh);
    auto z_sh = std::static_pointer_cast<const TestObject>(y_sh);
    BOOST_TEST( z_sh == x_sh );
}

BOOST_AUTO_TEST_CASE( StdTypeIndexComparesTypeidValues )
{
    // -- check that the std::type_index's equality operator compares typeid values.

    auto y_ti = std::type_index(typeid(TestObject));
    BOOST_TEST( y_ti == typeid(TestObject) );
    auto z_ti = std::type_index(typeid(const TestObject));
    BOOST_TEST( z_ti == y_ti );
}

BOOST_AUTO_TEST_SUITE_END() // StdPreliminaryTests

//..............................................................................

BOOST_AUTO_TEST_CASE( ByteSizeTest )
{
    // -- check <c>any_handle</c>'s bytes size (must be ~ shared pointer's size + raw pointer's size).
    BOOST_TEST( sizeof(solo::any_handle) == sizeof(std::shared_ptr<void>) + sizeof(void*) );
}

BOOST_AUTO_TEST_CASE( DefaultStateTest )
{
    // -- check the default <c>any_handle</c> state (must be empty)
    solo::any_handle ah{};
    BOOST_TEST( ah.empty() );

    // ... what "empty" implies:
    BOOST_TEST( ah.type() == typeid(void) );
    BOOST_TEST( ah.pointer() == nullptr );
    BOOST_TEST( ah.is_mutable() == false );
    BOOST_TEST( ah.mutable_pointer() == nullptr );
}

BOOST_AUTO_TEST_CASE( ExplicitArgumentCopyConstructorTest_GivenDefaultSharedPointer )
{
    // -- check the explicit argument-based copy constructor for non-mutable <c>any_handle</c> (from null typed shared pointer).

    // given a non-mutable shared pointer of some type T.
    using T = int; // work also with type `void`
    auto y_sp = std::shared_ptr<const T>{}; // a null non-mutable shared pointer of type T
    // create a non-mutable type-erased handle that catches it:
    auto y_ti = solo::make_any_type_index<T>(solo::mutability::false_);
    auto y_sh = std::const_pointer_cast<void>(std::static_pointer_cast<const void>(y_sp)); // must be shared_ptr<void>
    any_handle_ex ah{y_ti, y_sh};
    // check handle's state:
    BOOST_TEST( ah.empty() == false );
    BOOST_TEST( ah.type() == typeid(T) );
    BOOST_TEST( ah.pointer() == nullptr );
    BOOST_TEST( ah.is_mutable() == false );
    BOOST_TEST( ah.mutable_pointer() == nullptr );
}

BOOST_AUTO_TEST_CASE( ExplicitArgumentCopyConstructorTest_GivenDefaultSharedPointer_UsingConstTypeInformation )
{
    // -- check the explicit argument-based copy constructor for non-mutable <c>any_handle</c> (using const type ti).
    // the recorded type information should be const-removed

    // given a non-mutable shared pointer of some type T.
    using T = int; // work also with type `void`
    auto y_sp = std::shared_ptr<const T>{}; // a null non-mutable shared pointer of type T
    // create a non-mutable type-erased handle that catch it:
    auto y_ti = solo::make_any_type_index<const T>(solo::mutability::false_); // use a `const T` type information
    auto y_sh = std::const_pointer_cast<void>(std::static_pointer_cast<const void>(y_sp)); // must be shared_ptr<void>
    any_handle_ex ah{y_ti, y_sh};
    // check handle's state:
    BOOST_TEST( ah.empty() == false );
    BOOST_TEST( ah.type() == typeid(T) );
    BOOST_TEST( ah.pointer() == nullptr );
    BOOST_TEST( ah.is_mutable() == false );
    BOOST_TEST( ah.mutable_pointer() == nullptr );
}

BOOST_AUTO_TEST_CASE( ExplicitArgumentCopyConstructorTest_GivenNonMutableSharedObject )
{
    // -- check the explicit argument-based copy constructor for non-mutable <c>any_handle</c> (from an existing non-mutable shared object).

    // given an existing non-mutable shared object:
    auto x_sh = std::make_shared<const TestObject>();
    // create a non-mutable type-erased handle that catch it:
    auto y_ti = solo::make_any_type_index<const TestObject>(solo::mutability::false_);
    auto y_sh = std::const_pointer_cast<void>(std::static_pointer_cast<const void>(x_sh));
    any_handle_ex ah{y_ti, y_sh};
    // check handle's state:
    BOOST_TEST( ah.empty() == false );
    BOOST_TEST( ah.type() == typeid(const TestObject) );
    BOOST_TEST( ah.pointer() == x_sh );
    BOOST_TEST( ah.is_mutable() == false );
    BOOST_TEST( ah.mutable_pointer() == nullptr );
}

BOOST_AUTO_TEST_CASE( ExplicitArgumentCopyConstructorTest_GivenMutableSharedObject)
{
    // -- check the explicit argument-based copy constructor for non-mutable <c>any_handle</c> (from an existing mutable shared object)

    // given an existing mutable shared object:
    auto x_sp = std::make_shared<TestObject>();
    // create a non-mutable type-erased handle that catch it:
    auto y_ti = solo::make_any_type_index<TestObject>(solo::mutability::false_);
    auto y_sp = std::static_pointer_cast<void>(x_sp); // must be shared_ptr<void>
    any_handle_ex ah{y_ti, y_sp};
    // check handle's state:
    BOOST_TEST( ah.empty() == false );
    BOOST_TEST( ah.type() == typeid(TestObject) );
    BOOST_TEST( ah.pointer() == x_sp );
    BOOST_TEST( ah.is_mutable() == false );
    BOOST_TEST( ah.mutable_pointer() == nullptr );
}

BOOST_AUTO_TEST_CASE( ExplicitArgumentCopyConstructorTest_GivenDerivedSharedObject )
{
    // -- check the explicit argument-based copy constructor for non-mutable <c>any_handle</c> (from a mutable base pointer to an existing mutable shared object)

    // given an existing derived shared object:
    auto x_sp = std::make_shared<TestObject>(); // TestObject is dervied from TestObjectBase
    // create a non-mutable type-erased handle that catches its base interface:
    auto y_ti = solo::make_any_type_index<TestObjectBase>(solo::mutability::false_);
    auto y_sh = std::static_pointer_cast<void>(x_sp);
    any_handle_ex ah{y_ti, y_sh};
    // check handle's type:
    BOOST_TEST( ah.type() == typeid(TestObjectBase) );
}

BOOST_AUTO_TEST_CASE( ExplicitMutableArgumentCopyConstructorTest_GivenMutableSharedObject )
{
    // -- check the explicit argument-based copy constructor for mutable <c>any_handle</c> (from an existing mutable shared object).

    auto x_sp = std::make_shared<TestObject>();
    auto y_ti = solo::make_any_type_index<TestObject>(solo::mutability::true_);
    auto y_sh = std::static_pointer_cast<void>(x_sp);
    any_handle_ex ah{y_ti, y_sh};
    BOOST_TEST( ah.empty() == false );
    BOOST_TEST( ah.type() == typeid(TestObject) );
    BOOST_TEST( ah.pointer() == x_sp );
    BOOST_TEST( ah.is_mutable() == true );
    BOOST_TEST( ah.mutable_pointer() == x_sp );
}

BOOST_AUTO_TEST_CASE( ExplicitArgumentMoveConstructorTest )
{
    // -- check the explicit argument-based move constructor for non-mutable any handle.

    // given a temporary non-mutable typed shared object:
    using T = const TestObject;
    auto x_sp = std::make_shared<T>();
    // create a type-erased handle by moving the source object:
    auto y_ti = solo::make_any_type_index<T>(solo::mutability::false_);
    auto y_sh = std::const_pointer_cast<void>(std::static_pointer_cast<const void>(x_sp));
    any_handle_ex ah{y_ti, std::move(y_sh)};
    // check handle's state:
    BOOST_TEST( y_sh == nullptr );
    BOOST_TEST( ah.empty() == false );
    BOOST_TEST( ah.type() == typeid(T) );
    BOOST_TEST( ah.is_mutable() == false );
    BOOST_TEST( ah.mutable_pointer() == nullptr );// because ah is non-mutable
    BOOST_TEST( ah.pointer() != y_sh );// because y_sh has been move
}

BOOST_AUTO_TEST_CASE( UseCountTest_GivenExplicitArgumentCopyConstructedAnyHandle )
{
    // -- check the uses count of an object shared through <c>any_handle</c>.

    using T = TestObject;
    auto x_sp = std::make_shared<T>();
    BOOST_TEST( x_sp.use_count() == 1 );
    auto y_ti = solo::make_any_type_index<T>(solo::mutability::false_);
    auto y_sh = std::static_pointer_cast<void>(x_sp);
    BOOST_TEST( x_sp.use_count() == 2 );// 1 for x_sp + 1 for y_sh
    any_handle_ex ah{y_ti, y_sh};
    BOOST_TEST( x_sp.use_count() == 3 );// 1 for x_sp + 1 for y_sh + 1 for ah's internal
    auto z_sh = ah.pointer();
    BOOST_TEST( x_sp.use_count() == 4 );// + 1 for ah's pointer()
}

BOOST_AUTO_TEST_CASE( UseCountTest_GivenExplicitArgumentMoveConstructedAnyHandle )
{
    // -- check the uses count of an object shared through <c>any_handle</c>.

    using T = const TestObject;
    auto x_sp = std::make_shared<T>();
    BOOST_TEST( x_sp.use_count() == 1 );
    auto y_ti = solo::make_any_type_index<T>(solo::mutability::false_);
    auto y_sh = std::const_pointer_cast<void>(std::static_pointer_cast<const void>(x_sp));
    BOOST_TEST( x_sp.use_count() == 2 );// 1 for x_sp + 1 for y_sh
    any_handle_ex ah{y_ti, std::move(y_sh)};
    BOOST_TEST( x_sp.use_count() == 2 );// 1 for x_sp + 1 for ah's internal (y_sh is reset)
    auto z_sh = ah.pointer();
    BOOST_TEST( x_sp.use_count() == 3 );// + 1 for ah's pointer()
}

BOOST_AUTO_TEST_CASE( FactoryTest_01 )
{
    // -- check the <c>any handle</c> factory.

    // given:
    using x_type = TestObject;
    auto x_sp = std::make_shared<x_type>();
    // creates a type-erased handle on it
    auto ah = solo::make_any_handle(x_sp);
    static_assert(std::is_same<decltype(ah), solo::any_handle>::value, "");
    BOOST_TEST( ah.type() == typeid(x_type) );
    BOOST_TEST( ah == x_sp );
    // create a type-erased handle from another shared pointer on the shared source object:
    auto y_sp = std::static_pointer_cast<const x_type>(x_sp);
    BOOST_TEST( y_sp == x_sp );
    auto bh = solo::make_any_handle(y_sp);
    static_assert(std::is_same<decltype(bh), solo::any_handle>::value, "");
    BOOST_TEST( bh.type() == typeid(x_type) );
    BOOST_TEST( bh == ah );
}

BOOST_AUTO_TEST_CASE( FactoryTest_02 )
{
    // -- check the <c>any handle</c> factory.

    // given:
    using x_type = TestObject;
    using x_base_type = TestObjectBase;
    static_assert(std::is_base_of<x_base_type, x_type>::value, "");
    auto x_sp = std::make_shared<x_type>();
    // creates a type-erased handle on the base type:
    auto ah = solo::make_any_handle<x_base_type>(x_sp);
    BOOST_TEST( ah.type() == typeid(x_base_type) );
    BOOST_TEST( ah == x_sp );
    // create a type-erased handle from another shared pointer on the shared source object's base:
    auto y_sh = std::static_pointer_cast<const x_base_type>(x_sp);
    BOOST_TEST( y_sh == x_sp );
    auto bh = solo::make_any_handle(y_sh);
    BOOST_TEST( bh.type() == typeid(x_base_type) );
    BOOST_TEST( bh == ah );
}

BOOST_AUTO_TEST_CASE( FactoryTest_03 )
{
    // -- check the <c>any handle</c> factory.

    // given:
    using x_type = TestObject;
    auto x_sp = std::make_shared<x_type>();
    assert(x_sp.use_count() == 1);
    auto y_sp = std::shared_ptr<const x_type>(x_sp);
    assert(x_sp == y_sp);
    assert(x_sp.use_count() == 2);
    //
    auto ah = solo::make_any_handle<x_type>(std::move(y_sp));
    BOOST_TEST( ah == x_sp );
    BOOST_TEST( ah.type() == typeid(x_type) );
    BOOST_TEST( ah.use_count() == 3);
}

BOOST_AUTO_TEST_CASE( FactoryTest_04 )
{
    // -- check the <c>any handle</c> factory.

    // given:
    using x_type = TestObject;
    using x_base_type = TestObjectBase;
    static_assert(std::is_base_of<x_base_type, x_type>::value, "");
    auto x_sp = std::make_shared<x_type>();
    assert(x_sp.use_count() == 1);
    auto y_sp = std::static_pointer_cast<x_base_type>(x_sp);
    assert(x_sp == y_sp);
    assert(x_sp.use_count() == 2);
    //
    auto ah = solo::make_any_handle<x_base_type>(std::move(y_sp));
    BOOST_TEST( ah == x_sp );
    BOOST_TEST( ah.type() == typeid(x_base_type) );
    BOOST_TEST( ah.use_count() == 3);
}

BOOST_AUTO_TEST_CASE( CopyConstructorTest )
{
    // check the copy constructor

    using solo::make_any_handle;
    using solo::any_handle;

    auto x_sh = std::make_shared<TestObject>();
    auto ah = make_any_handle(x_sh);
    any_handle bh{ah};
    BOOST_TEST( bh.type() == ah.type() );
    BOOST_TEST( bh.pointer() == ah.pointer() );
}

BOOST_AUTO_TEST_CASE( MoveConstructorTest )
{
    // check the move constructor

    using solo::make_any_handle;
    using solo::any_handle;

    auto x_sh = std::make_shared<TestObject>();
    auto ah = make_any_handle(x_sh);
    any_handle bh{std::move(ah)};
    BOOST_TEST( bh.type() == ah.type() );
    BOOST_TEST( bh.pointer() == x_sh );
    BOOST_TEST( ah.pointer() == nullptr );
}

BOOST_AUTO_TEST_CASE( CopyOperatorTest )
{
    // check the copy operator

    using solo::make_any_handle;
    using solo::any_handle;

    auto x_sh = std::make_shared<TestObject>();
    auto ah = make_any_handle(x_sh);
    BOOST_TEST( ah.empty() == false );
    any_handle bh{};
    BOOST_TEST( bh.empty() == true );
    bh = ah;
    BOOST_TEST( bh.empty() == false );
    BOOST_TEST( bh.type() == ah.type() );
    BOOST_TEST( bh.pointer() == ah.pointer() );
}

BOOST_AUTO_TEST_CASE( MoveOperatorTest )
{
    // check the move operator

    using solo::make_any_handle;
    using solo::any_handle;

    auto x_sh = std::make_shared<TestObject>();
    auto ah = make_any_handle(x_sh);
    BOOST_TEST( ah.empty() == false );
    any_handle bh{};
    BOOST_TEST( bh.empty() == true );
    bh = std::move(ah);
    BOOST_TEST( bh.empty() == false );
    BOOST_TEST( bh.type() == ah.type() );
    BOOST_TEST( bh.pointer() == x_sh );
    BOOST_TEST( ah.pointer() == nullptr );
}

BOOST_AUTO_TEST_CASE( SwapTest )
{
    // -- check the swapping operation.

    // given a first shared object and a type-erased handle on it:
    using T = TestObject;
    auto x_sp = std::make_shared<T>();
    auto ah = solo::make_any_handle(x_sp);
    assert( ah == x_sp );
    assert( x_sp.use_count() == 2 );
    // given a seccond shared object and a type-erased handle on it:
    auto y_sp = std::make_shared<T>();
    auto bh = solo::make_any_handle(y_sp);
    assert( bh == y_sp );
    assert( y_sp.use_count() == 2 );
    // swap handles' states:
    std::swap(x_sp, y_sp);
    BOOST_TEST( ah == y_sp );
    BOOST_TEST( bh == x_sp );
    assert( x_sp.use_count() == 2 );
    assert( y_sp.use_count() == 2 );
}

BOOST_AUTO_TEST_CASE( EqualityOperatorTest )
{
    // -- check the comparison operation.

    // given a shared object and a type-erased handle on it:
    using T = TestObject;
    auto x_sp = std::make_shared<T>();
    auto ah = solo::make_any_handle(x_sp);
    // check that the type-erased handle compares to the source object's pointer value:
    BOOST_TEST( ah == x_sp );
    // check that the type-erased handle compares to nullptr:
    BOOST_TEST( ah != nullptr );
    // check that type-erased handle compares to type-erased handle.
    auto ah2 = solo::any_handle{ah};
    BOOST_TEST( ah == ah2 );

    // given a second shared object and a type-erased handle on it:
    auto y_sp = std::make_shared<T>();
    auto bh = solo::make_any_handle(y_sp);
    // check that type-erased handle compares to type-erased handle.
    BOOST_TEST( bh != ah );

    // check that the default <c>any_handle</c> equals nullptr:
    solo::any_handle ch{};
    BOOST_TEST( ch == nullptr );

    // check that a type-erased handle on base and a type-erased handle on derived equal the same raw pointer value:
    using Base = TestObjectBase;
    auto dh = solo::make_any_handle<const Base>(x_sp);
    BOOST_TEST( dh == ah );
}

//..............................................................................

BOOST_AUTO_TEST_CASE( BasicUsage_01 )
{
    struct A {
        int data{};
        A(int n) : data{n} {};
    };
    auto x = std::make_shared<const A>(1);
    assert(x.use_count() == 1);

    auto y = solo::make_any_handle(x);// keep a _copy_ of x
    static_assert(std::is_same<decltype(y), solo::any_handle>::value, "");
    BOOST_TEST(x.use_count() == 2);
    BOOST_TEST(y.pointer() == x);
    BOOST_TEST(y.type() == typeid(A));
    auto rz = solo::any_handle_cast<A>(y);
    BOOST_TEST(rz.has_value());
    auto const &z = rz.assume_value();
    static_assert(std::is_same<decltype(z), std::shared_ptr<const A> const &>::value, "");
    BOOST_TEST(x.use_count() == 3);
    BOOST_TEST(z == x);
}

BOOST_AUTO_TEST_CASE( BasicUsage_02 )
{
    constexpr auto const verboseOutputs = false;

    class DriverInterface {
    public :
        virtual ~DriverInterface() = default;
        virtual void doWork() = 0;
    };

    class ConcreteDriver : public DriverInterface {
        std::ostringstream _output{};
    public :
        void doWork() override {
            _output << "working..." << std::endl;
        };
    };
    auto reg = std::map<std::string, solo::any_handle>{};
    {
        auto x = std::make_shared<ConcreteDriver>();
        reg["the_driver"] = solo::make_any_handle_mutable<DriverInterface>(x);
    }
    {
        auto &ah = reg["the_driver"];
        auto ri = solo::any_handle_mutable_cast<DriverInterface>(ah).assume_move_value();
        ri->doWork();
    }
    {
        try
        {
            auto const &rh = reg["the_driver"];
            // throw a bad cast exception (should have cast to DriverInterface) :
            auto ri = solo::any_handle_cast_or_throw<ConcreteDriver>(rh);
        }
        catch (solo::anys::exceptions::bad_any_handle_cast const &ex)
        {
            if (verboseOutputs)
            {
                using solo::testing::operator<<;
                std::cout << ex << std::endl;
            }
        }
    }
}

//..............................................................................

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
}}// EONS SOLOTESTS
////////////////////////////////////////////////////////////////////////////////
