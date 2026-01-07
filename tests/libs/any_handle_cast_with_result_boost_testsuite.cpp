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
#include <stdex/typeindex/testing/printing/std_type_index_boost_test_outputters.hpp>

#include <boost/test/unit_test.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace tests {
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( SoloAnyHandleTestSuite )

//..............................................................................

BOOST_AUTO_TEST_CASE( NonMutableHandleNonMutableCast_SuccessTest )
{
    // check the successful non-mutable cast operation on non-mutable handle :

    auto const x_sh = std::make_shared<TestObject>();
    auto const a_sh = solo::make_any_handle(x_sh);// copy x_sh

    auto const r_sh = solo::any_handle_cast<TestObject>(a_sh);
    static_assert( std::is_same<decltype(r_sh),solo::any_handle_cast_result_type<TestObject> const>::value,"" );
    BOOST_TEST( not r_sh.has_error() );
    BOOST_TEST( r_sh.has_value() );

    auto const &y_sh = r_sh.assume_value();
    static_assert( std::is_same<decltype(y_sh),std::shared_ptr<TestObject const> const &>::value,"" );
    BOOST_TEST( y_sh == x_sh );

    auto r_mutable = r_sh;// a mutable copy
    auto y_moved = std::move(r_mutable).assume_move_value();// build w_sh by moving result's value
    static_assert( std::is_same<decltype(y_moved),std::shared_ptr<TestObject const>>::value,"" );
    BOOST_TEST( not r_mutable.has_error() );
    BOOST_TEST( r_mutable.has_value() );// result still has value but value has been moved
    BOOST_TEST(( r_mutable.assume_value() == nullptr ));
    BOOST_TEST( y_moved == x_sh );
}

BOOST_AUTO_TEST_CASE( NonMutableHandleNonMutableCast_WithConstTargetType_SuccessTest )
{
    // check the non-mutable cast curiosity:

    auto x_sh1 = std::make_shared<TestObject>();
    auto a_sh1 = solo::make_any_handle(x_sh1);// a non-mutable any handle

    auto y_sh1 = solo::any_handle_cast<TestObject const>(a_sh1).assume_value();// a non-mutable cast doubled with a const target type
    auto z_sh1 = solo::any_handle_cast<TestObject>(a_sh1).assume_value();// a simple non-mutable cast
    BOOST_TEST(y_sh1 == z_sh1);
    auto const &expected_type_info = typeid(std::shared_ptr<TestObject const>);
    BOOST_TEST(typeid(y_sh1) == expected_type_info);
    BOOST_TEST(typeid(z_sh1) == expected_type_info);
}

BOOST_AUTO_TEST_CASE( NonMutableHandleNonMutableCast_WithBaseTargetType_SuccessTest )
{
    // check the successfull non-mutable cast operation on non-mutable handle with base target type :

    auto x_sh1 = std::make_shared<TestObject const>(1);
    auto x_sh2 = std::make_shared<TestObject>(2);
    auto a_sh1 = solo::make_any_handle<TestObjectBase const>(x_sh1);
    auto a_sh2 = solo::make_any_handle<TestObjectBase>(x_sh2);

    auto r_sh1 = solo::any_handle_cast<TestObjectBase>(a_sh1);
    auto y_sh1 = std::move(r_sh1).assume_value();
    static_assert( std::is_same<decltype(y_sh1),std::shared_ptr<TestObjectBase const>>::value,"" );
    BOOST_TEST( y_sh1->data() == 1 );// call TestObject::data

    auto r_sh2 = solo::any_handle_cast<TestObjectBase>(a_sh2);
    auto y_sh2 = std::move(r_sh2).assume_value();
    static_assert( std::is_same<decltype(y_sh2),std::shared_ptr<TestObjectBase const>>::value,"" );
    BOOST_TEST( y_sh2->data() == 2 );// call TestObject::data

    auto z_sh2 = std::const_pointer_cast<TestObjectBase>(y_sh2);// source object is mutable
    z_sh2->setdata(3);// call TestObject::setdata
    BOOST_TEST( z_sh2->data() == 3 );
}

BOOST_AUTO_TEST_CASE( MutableHandleMutableCast_WithConstTargetType_SuccessTest )
{
    // check the mutable cast curiosity :

    auto x_sh1 = std::make_shared<TestObject>(1);
    auto a_sh1 = solo::make_any_handle_mutable(x_sh1);// a mutable any handle

    auto y_sh1 = solo::any_handle_mutable_cast<TestObject const>(a_sh1).assume_value();// a mutable cast countered by a const target type
    auto z_sh1 = solo::any_handle_cast<TestObject>(a_sh1).assume_value();// a simple non-mutable cast
    BOOST_TEST(y_sh1 == z_sh1);
    auto const &expected_type_info = typeid(std::shared_ptr<TestObject const>);
    BOOST_TEST(typeid(y_sh1) == expected_type_info);
    BOOST_TEST(typeid(z_sh1) == expected_type_info);
}

BOOST_AUTO_TEST_CASE( EmptyHandleNonMutableCast_FailureTest )
{
    // check the casting operation

    auto const a_sh = solo::any_handle{};// empty_handle

    auto const r_sh = solo::any_handle_cast<void>(a_sh);
    static_assert( std::is_same<decltype(r_sh),solo::any_handle_cast_result_type<void> const>::value,"" );
    BOOST_TEST(not r_sh.has_value());
    BOOST_TEST(r_sh.has_error());

    auto const &e_sh = r_sh.assume_error();
    static_assert( std::is_same<decltype(e_sh),solo::anys::errors::any_handle_cast_error const &>::value,"" );
    BOOST_TEST(( solo::anys::errors::is_empty_source_error(e_sh) ));

    auto r_mutable = r_sh;// make a mutable copy
    auto e_moved = std::move(r_mutable).assume_move_error();// move the error and leave the result moved
    static_assert( std::is_same<decltype(e_moved),solo::anys::errors::any_handle_cast_error>::value,"" );
    BOOST_TEST( not r_mutable.has_value() );
    BOOST_TEST( r_mutable.has_error() );// result still has error but error has been moved
    BOOST_TEST(( r_mutable.assume_error().code() == solo::anys::errors::any_handle_cast_errc::undefined ));
    BOOST_TEST(( solo::anys::errors::is_empty_source_error(e_moved) ));
}

BOOST_AUTO_TEST_CASE( NonMutableHandleNonMutableCast_WithBadType_FailureTest )
{
    // check the casting operation

    auto const x_sh1 = std::make_shared<TestObject>(1);
    auto const a_sh1 = solo::make_any_handle<TestObjectBase const>(x_sh1);// copy x_sh1

    auto const r_sh1 = solo::any_handle_cast<int>(a_sh1);
    static_assert( std::is_same<decltype(r_sh1),solo::any_handle_cast_result_type<int> const>::value,"" );
    BOOST_TEST(not r_sh1.has_value());
    BOOST_TEST(r_sh1.has_error());

    auto const &e_sh1 = r_sh1.assume_error();
    static_assert( std::is_same<decltype(e_sh1),solo::anys::errors::any_handle_cast_error const &>::value,"" );
    BOOST_TEST(( solo::anys::errors::is_bad_source_type_error(e_sh1) ));
}

BOOST_AUTO_TEST_CASE( NonMutableHandleNonMutableCastWithBadBaseType_FailureTest )
{
    // check the casting operation

    auto const x_sh1 = std::make_shared<TestObject>(1);
    auto const a_sh1 = solo::make_any_handle<TestObjectBase const>(x_sh1);// copy x_sh1

    auto const r_sh2 = solo::any_handle_cast<TestObject>(a_sh1);
    static_assert( std::is_same<decltype(r_sh2),solo::any_handle_cast_result_type<TestObject> const>::value,"" );
    BOOST_TEST(not r_sh2.has_value());
    BOOST_TEST(r_sh2.has_error());

    auto const &e_sh2 = r_sh2.assume_error();
    static_assert( std::is_same<decltype(e_sh2),solo::anys::errors::any_handle_cast_error const &>::value,"" );
    BOOST_TEST(( solo::anys::errors::is_bad_source_type_error(e_sh2) ));
}

BOOST_AUTO_TEST_CASE( NonMutableHandleMutableCast_FailureTest )
{
    // check the casting operation

    auto const x_sh1 = std::make_shared<TestObject>(1);
    auto const a_sh1 = solo::make_any_handle<TestObjectBase const>(x_sh1);// copy x_sh1

    auto const r_sh3 = solo::any_handle_mutable_cast<TestObjectBase>(a_sh1);
    static_assert( std::is_same<decltype(r_sh3),solo::any_handle_mutable_cast_result_type<TestObjectBase> const>::value,"" );
    BOOST_TEST(not r_sh3.has_value());
    BOOST_TEST(r_sh3.has_error());

    auto const &e_sh3 = r_sh3.assume_error();
    static_assert( std::is_same<decltype(e_sh3),solo::anys::errors::any_handle_cast_error const &>::value,"" );
    BOOST_TEST(( solo::anys::errors::is_bad_source_mutability_error(e_sh3) ));
}

//..............................................................................

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLOTESTS
////////////////////////////////////////////////////////////////////////////////
