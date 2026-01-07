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

BOOST_AUTO_TEST_CASE( CastOrThrowTest_01 )
{
    // check the casting operation

    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;

    auto x_sh = std::make_shared<TestObject>();
    auto a_sh = make_any_handle(x_sh);

    auto y_sh = any_handle_cast_or_throw<TestObject>(a_sh);
    BOOST_TEST( y_sh == x_sh );
    BOOST_TEST( typeid(y_sh) == typeid(std::shared_ptr<const TestObject>) );
    auto z_sh = any_handle_cast_or_throw<const TestObject>(a_sh);
    BOOST_TEST( typeid(z_sh) == typeid(std::shared_ptr<const TestObject>) );
    BOOST_TEST( z_sh == x_sh );
}

BOOST_AUTO_TEST_CASE( CastOrThrowTest_02 )
{
    // check the casting operation

    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;

    auto x_sh1 = std::make_shared<const TestObject>(1);
    auto x_sh2 = std::make_shared<TestObject>(2);
    auto a_sh1 = make_any_handle<const TestObjectBase>(x_sh1);
    auto a_sh2 = make_any_handle<TestObjectBase>(x_sh2);

    auto y_sh1 = any_handle_cast_or_throw<TestObjectBase>(a_sh1);
    BOOST_TEST( typeid(y_sh1) == typeid(std::shared_ptr<const TestObjectBase>) );
    BOOST_TEST( y_sh1->data() == 1 );
    auto y_sh2 = any_handle_cast_or_throw<TestObjectBase>(a_sh2);
    BOOST_TEST( typeid(y_sh2) == typeid(std::shared_ptr<const TestObjectBase>) );
    BOOST_TEST( y_sh2->data() == 2 );
    auto z_sh2 = std::const_pointer_cast<TestObjectBase>(y_sh2);
    z_sh2->setdata(3);
    BOOST_TEST( z_sh2->data() == 3 );
}

BOOST_AUTO_TEST_CASE( CastOrThrowTest_03 )
{
    // check the casting operation

    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;
    using solo::any_handle_mutable_cast_or_throw;
    using solo::anys::exceptions::bad_any_handle_cast;

    auto x_sh1 = std::make_shared<TestObject>(1);
    auto a_sh1 = make_any_handle<const TestObjectBase>(x_sh1);
    BOOST_CHECK_THROW( auto y_sh1 = any_handle_cast_or_throw<int>(a_sh1), bad_any_handle_cast );
    BOOST_CHECK_THROW( auto y_sh2 = any_handle_cast_or_throw<TestObject>(a_sh1), bad_any_handle_cast );
    BOOST_CHECK_THROW( auto y_sh3 = any_handle_mutable_cast_or_throw<TestObjectBase>(a_sh1), bad_any_handle_cast );
    try
    {
        auto y_sh = any_handle_cast_or_throw<TestObject>(a_sh1);
    }
    catch (bad_any_handle_cast const &ex)
    {
        BOOST_TEST(ex.actual().type == typeid(TestObjectBase));
        BOOST_TEST(ex.expected().type == typeid(TestObject));
    }
    try
    {
        auto y_sh = any_handle_mutable_cast_or_throw<TestObjectBase>(a_sh1);
    }
    catch (bad_any_handle_cast const &ex)
    {
        BOOST_TEST(ex.actual().mutability == false);
        BOOST_TEST(ex.expected().mutability == true);
    }
}

BOOST_AUTO_TEST_CASE( CastOrThrowTest_04 )
{
    // check the non-mutable any_handle_cast_or_throw curiosity:

    using solo::make_any_handle;
    using solo::any_handle_cast_or_throw;

    auto x_sh1 = std::make_shared<TestObject>(1);
    auto a_sh1 = make_any_handle(x_sh1);// a non-mutable any handle

    auto y_sh1 = any_handle_cast_or_throw<const TestObject>(a_sh1);// a non-mutable cast doubled with a const target type
    auto z_sh1 = any_handle_cast_or_throw<TestObject>(a_sh1);// a simple non-mutable cast
    BOOST_TEST(y_sh1 == z_sh1);
    auto const &expected_type_info = typeid(std::shared_ptr<const TestObject>);
    BOOST_TEST(typeid(y_sh1) == expected_type_info);
    BOOST_TEST(typeid(z_sh1) == expected_type_info);
}

BOOST_AUTO_TEST_CASE( CastOrThrowTest_05 )
{
    // check the mutable any_handle_cast_or_throw curiosity:

    using solo::make_any_handle_mutable;
    using solo::any_handle_mutable_cast_or_throw;
    using solo::any_handle_cast_or_throw;

    auto x_sh1 = std::make_shared<TestObject>(1);
    auto a_sh1 = make_any_handle_mutable(x_sh1);// a mutable any handle

    auto y_sh1 = any_handle_mutable_cast_or_throw<const TestObject>(a_sh1);// a mutable cast countered by a const target type
    auto z_sh1 = any_handle_cast_or_throw<TestObject>(a_sh1);// a simple non-mutable cast
    BOOST_TEST(y_sh1 == z_sh1);
    auto const &expected_type_info = typeid(std::shared_ptr<const TestObject>);
    BOOST_TEST(typeid(y_sh1) == expected_type_info);
    BOOST_TEST(typeid(z_sh1) == expected_type_info);
}

//..............................................................................

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
}}// EONS SOLOTESTS
////////////////////////////////////////////////////////////////////////////////
