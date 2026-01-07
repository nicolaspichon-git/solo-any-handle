//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------

#include "any_handle_testsuite_types.hpp"

#include <solo/anys/handles/any_handle_package.hpp>
#include <stdex/testing/printing/typeindex/std_type_index_boost_test_outputters.hpp>

#include <boost/test/unit_test.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace tests {
////////////////////////////////////////////////////////////////////////////////

//..............................................................................

BOOST_AUTO_TEST_SUITE( SoloAnyHandleTestSuite )

//..............................................................................

BOOST_AUTO_TEST_CASE( FactoryInPlaceTest )
{
    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;

    // built the non-mutable object TestObject{1} in-place :
    auto a_sh1 = make_any_handle<TestObject>( stdex::in_place, 1 );
    BOOST_TEST(a_sh1.use_count() == 1);
    BOOST_TEST(a_sh1.type() == typeid(TestObject));
    BOOST_TEST(a_sh1.is_mutable() == false);
    BOOST_TEST(a_sh1.mutable_pointer() == nullptr);
    auto y_sh1 = any_handle_cast_or_throw<const TestObject>(a_sh1);
    BOOST_TEST(y_sh1 == a_sh1.pointer());
    BOOST_TEST(y_sh1->data() == 1);

    // check that the object TestObject{"3"} cannot be built in-place :
    // should not compile :
    // auto a_sh3 = make_any_handle<TestObject>( stdex::in_place, "3" );
}

BOOST_AUTO_TEST_CASE( FactoryMutableInPlaceTest )
{
    using solo::make_any_handle_mutable;
    using solo::any_handle_cast_or_throw;

    // built the mutable object TestObject{1} in-place :
    auto a_sh1 = make_any_handle_mutable<TestObject>( stdex::in_place, 1 );
    BOOST_TEST(a_sh1.use_count() == 1);
    BOOST_TEST(a_sh1.type() == typeid(TestObject));
    BOOST_TEST(a_sh1.is_mutable() == true);
    BOOST_TEST(a_sh1.mutable_pointer() == a_sh1.pointer());
    auto y_sh1 = any_handle_cast_or_throw<const TestObject>(a_sh1);
    BOOST_TEST(y_sh1 == a_sh1.pointer());
    BOOST_TEST(y_sh1 == a_sh1.mutable_pointer());
    BOOST_TEST(y_sh1->data() == 1);
}

BOOST_AUTO_TEST_CASE( FactoryInPlaceTypeTest )
{
    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;

    // built the non-mutable object TestObject{4} in-place and get back a shared pointer of type TestObjectBase :
    auto a_sh4 = make_any_handle<TestObjectBase>( stdex::in_place_type<TestObject>, 4 );
    BOOST_TEST(a_sh4.use_count() == 1);
    BOOST_TEST(a_sh4.type() == typeid(TestObjectBase));
    BOOST_TEST(a_sh4.is_mutable() == false);
    BOOST_TEST(a_sh4.mutable_pointer() == nullptr);
    auto y_sh4 = any_handle_cast_or_throw<TestObjectBase>(a_sh4);// or any_handle_cast_or_throw<const TestObjectBase>
    static_assert(std::is_same<decltype(y_sh4),std::shared_ptr<const TestObjectBase>>::value, "");
    BOOST_TEST(y_sh4 == a_sh4.pointer());
    BOOST_TEST(y_sh4->data() == 4);// should call TestObject::data
}

BOOST_AUTO_TEST_CASE( FactoryMutableInPlaceTypeTest )
{
    using solo::make_any_handle_mutable;
    using solo::any_handle_cast_or_throw;

    // built the mutable object TestObject{4} in-place and get back a shared pointer of type TestObjectBase :
    auto a_sh4 = make_any_handle_mutable<TestObjectBase>( stdex::in_place_type<TestObject>, 4 );
    BOOST_TEST(a_sh4.use_count() == 1);
    BOOST_TEST(a_sh4.type() == typeid(TestObjectBase));
    BOOST_TEST(a_sh4.is_mutable() == true);
    BOOST_TEST(a_sh4.mutable_pointer() == a_sh4.pointer());
    auto y_sh4 = any_handle_cast_or_throw<TestObjectBase>(a_sh4);// or any_handle_cast_or_throw<const TestObjectBase>
    static_assert(std::is_same<decltype(y_sh4),std::shared_ptr<const TestObjectBase>>::value, "");
    BOOST_TEST(y_sh4 == a_sh4.pointer());
    BOOST_TEST(y_sh4 == a_sh4.mutable_pointer());
    BOOST_TEST(y_sh4->data() == 4);// should call TestObject::data
}

BOOST_AUTO_TEST_CASE( FactoryObserverTest )
{
    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;

    auto x3 = TestObject{3};
    auto a_sh3 = make_any_handle( stdex::make_observer(&x3) );
    BOOST_TEST(a_sh3.use_count() == 1);
    BOOST_TEST(a_sh3.type() == typeid(TestObject));
    BOOST_TEST(a_sh3.is_mutable() == false);
    BOOST_TEST(a_sh3.mutable_pointer() == nullptr);
    BOOST_TEST(a_sh3.pointer().get() == &x3);
    auto y_sh3 = any_handle_cast_or_throw<const TestObject>(a_sh3);
    BOOST_TEST(y_sh3.get() == &x3);
    BOOST_TEST(y_sh3->data() == 3);
}

BOOST_AUTO_TEST_CASE( FactoryMutableObserverTest )
{
    using solo::make_any_handle_mutable;
    using solo::any_handle_cast_or_throw;

    auto x3 = TestObject{3};
    auto a_sh3 = make_any_handle_mutable( stdex::make_observer(&x3) );
    BOOST_TEST(a_sh3.use_count() == 1);
    BOOST_TEST(a_sh3.type() == typeid(TestObject));
    BOOST_TEST(a_sh3.is_mutable() == true);
    BOOST_TEST(a_sh3.pointer().get() == &x3);
    BOOST_TEST(a_sh3.mutable_pointer().get() == &x3);
    auto y_sh3 = any_handle_cast_or_throw<const TestObject>(a_sh3);
    BOOST_TEST(y_sh3.get() == &x3);
    BOOST_TEST(y_sh3->data() == 3);
}

BOOST_AUTO_TEST_CASE( FactoryFinalizerTest )
{
    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;
    using solo::any_handle_mutable_cast_or_throw;

    auto x4 = TestObject{4};
    {
        auto finalizer = [](TestObject *p){ p->setdata(0); };
        auto a_sh4 = make_any_handle( &x4, finalizer );
        BOOST_TEST(a_sh4.use_count() == 1);
        BOOST_TEST(a_sh4.type() == typeid(TestObject));
        BOOST_TEST(a_sh4.is_mutable() == false);
        BOOST_TEST(a_sh4.pointer().get() == &x4);
        BOOST_TEST(a_sh4.mutable_pointer() == nullptr);
        auto y_sh4 = any_handle_cast_or_throw<const TestObject>(a_sh4);
        BOOST_TEST(y_sh4.get() == &x4);
        BOOST_TEST(y_sh4->data() == 4);
    }
    BOOST_TEST(x4.data() == 0);
}

BOOST_AUTO_TEST_CASE( FactoryMutableFinalizerTest )
{
    using solo::make_any_handle_mutable;
    using solo::any_handle_mutable_cast_or_throw;
    using solo::any_handle_cast_or_throw;

    auto x4 = TestObject{4};
    {
        auto finalizer = [](TestObject *p){ p->setdata(0); };
        auto a_sh4 = make_any_handle_mutable( &x4, finalizer );
        BOOST_TEST(a_sh4.use_count() == 1);
        BOOST_TEST(a_sh4.type() == typeid(TestObject));
        BOOST_TEST(a_sh4.is_mutable() == true);
        BOOST_TEST(a_sh4.pointer().get() == &x4);
        auto y_sh4 = any_handle_cast_or_throw<const TestObject>(a_sh4);
        BOOST_TEST(y_sh4.get() == &x4);
        BOOST_TEST(y_sh4->data() == 4);
    }
    BOOST_TEST(x4.data() == 0);
}

//..............................................................................

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
}}// EONS SOLOTESTS
////////////////////////////////////////////////////////////////////////////////
