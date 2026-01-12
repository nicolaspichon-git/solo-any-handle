//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/testing/printing/any_handle_testing_outputters.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo {
////////////////////////////////////////////////////////////////////////////////

/// @ingroup SoloAnyHandleTestingPrinting
/// @ingroup SoloCoreTestingPrinting
/// @brief Ready-to-use <c>any_handle</c> boost test's printer.
/// @note Need to be declared in the same namespace than the type to print.
/// @see https://www.boost.org/doc/libs/1_xx_0/libs/test/doc/html/boost_test/test_output/test_tools_support_for_logging/testing_tool_output_disable.html
inline std::ostream &boost_test_print_type(std::ostream &a_os, any_handle const &a_ah)
{
    return solo::testing::operator<<(a_os, a_ah);
}

/// @ingroup SoloAnyHandleTestingPrinting
/// @ingroup SoloCoreTestingPrinting
/// @brief Ready-to-use <c>any_type_index</c> boost test's printer.
/// @note Need to be declared in the same namespace than the type to print.
/// @see https://www.boost.org/doc/libs/1_xx_0/libs/test/doc/html/boost_test/test_output/test_tools_support_for_logging/testing_tool_output_disable.html
inline std::ostream &boost_test_print_type(std::ostream &a_os, any_type_index const &a_ti)
{
    return solo::testing::operator<<(a_os, a_ti);
}

/// @ingroup SoloAnyHandleTestingPrinting
/// @ingroup SoloCoreTestingPrinting
/// @brief Ready-to-use <c>bad_any_handle_cast</c> boost test's printer.
/// @note Need to be declared in the same namespace than the type to print.
/// @see https://www.boost.org/doc/libs/1_xx_0/libs/test/doc/html/boost_test/test_output/test_tools_support_for_logging/testing_tool_output_disable.html
inline std::ostream &boost_test_print_type(std::ostream &a_os, anys::exceptions::bad_any_handle_cast const &a_cast_failure_exception)
{
    return solo::testing::operator<<(a_os, a_cast_failure_exception);
}

/// @ingroup SoloAnyHandleTestingPrinting
/// @ingroup SoloCoreTestingPrinting
/// @brief Ready-to-use <c>any_handle_cast_error</c> boost test's printer.
/// @note Need to be declared in the same namespace than the type to print.
/// @see https://www.boost.org/doc/libs/1_xx_0/libs/test/doc/html/boost_test/test_output/test_tools_support_for_logging/testing_tool_output_disable.html
inline std::ostream &operator<<(std::ostream &a_os, solo::anys::errors::any_handle_cast_error const &a_cast_error )
{
    return solo::testing::operator<<(a_os, a_cast_error);
}

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLO
////////////////////////////////////////////////////////////////////////////////
