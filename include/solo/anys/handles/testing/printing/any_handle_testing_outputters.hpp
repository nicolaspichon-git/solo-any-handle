//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/errors/any_handle_cast_error.hpp>
#include <solo/anys/handles/exceptions/bad_any_handle_cast.hpp>

#include <boost/core/demangle.hpp>
#include <ostream>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace testing {
////////////////////////////////////////////////////////////////////////////////

/// @ingroup SoloAnyHandleTesting
/// @ingroup SoloCoreTesting
/// @brief Ready-to-use <c>any_handle</c> outputter for <c>std::ostream</c>.
inline std::ostream &operator<<(std::ostream &a_os, solo::any_handle const &a_ah)
{
    a_os << a_ah.pointer()
       << "(" << boost::core::demangle(a_ah.type().name())
       << "@" << ( a_ah.is_mutable() ? "mutable" : "non-mutable" )
       << "@" << ( a_ah.empty() ? "empty" : "non-empty" )
       << ")";
    return a_os;
}

/// @ingroup SoloAnyHandleTesting
/// @ingroup SoloCoreTesting
/// @brief Ready-to-use <c>any_type_index</c> outputter for <c>std::ostream</c>.
inline std::ostream &operator<<(std::ostream &a_os, solo::any_type_index const &a_ti)
{
    a_os << boost::core::demangle(a_ti.external_type_index().name())
       << "@" << ( a_ti.is_type_mutable() ? "mutable" : "non-mutable" )
       << "@" << ( a_ti.is_type_empty() ? "empty" : "non-empty" ) ;
    return a_os;
}

/// @ingroup SoloAnyHandleTesting
/// @ingroup SoloCoreTesting
/// @brief Ready-to-use <c>anys::exceptions::bad_any_handle_cast::cast_info</c> outputter for <c>std::ostream</c>.
inline std::ostream &operator<<(std::ostream &a_os, solo::anys::exceptions::bad_any_handle_cast::cast_info const &a_ci)
{
    a_os << boost::core::demangle(a_ci.type.name())
       << "@" << ( a_ci.mutability ? "mutable" : "non-mutable" );
    return a_os;
}

/// @ingroup SoloAnyHandleTesting
/// @ingroup SoloCoreTesting
/// @brief Ready-to-use <c>anys::exceptions::bad_any_handle_cast</c> outputter for <c>std::ostream</c>.
inline std::ostream &operator<<(std::ostream &a_os, solo::anys::exceptions::bad_any_handle_cast const &a_cast_failure_exception)
{
    a_os << a_cast_failure_exception.what()
         << " : { "
         << "actual={" << a_cast_failure_exception.actual() << "}"
         << ", "
         << "expected={" << a_cast_failure_exception.expected() << "}"
         << " }";
    return a_os;
}

/// @ingroup SoloAnyHandleTesting
/// @ingroup SoloCoreTesting
/// @brief Ready-to-use <c>anys::errors::any_handle_cast_error::code_type</c> outputter for <c>std::ostream</c>.
inline std::ostream &operator<<(std::ostream &a_os, solo::anys::errors::any_handle_cast_error::code_type const &a_cast_error_code )
{
    using errc_t = solo::anys::errors::any_handle_cast_error::code_type;

    auto message = [](errc_t code) -> const char *
    {
        switch(code)
        {
            case  errc_t::empty_source:
                return "empty source";
            case  errc_t::bad_source_type:
                return "bad source type";
            case  errc_t::bad_source_mutability:
                return "bad source mutability";
            default:
                return "undefined";
        };
    };

    a_os << message(a_cast_error_code);
    return a_os;
}

/// @ingroup SoloAnyHandleTesting
/// @ingroup SoloCoreTesting
/// @brief Ready-to-use <c>anys::errors::any_handle_cast_error</c> outputter for <c>std::ostream</c>.
inline std::ostream &operator<<(std::ostream &a_os, solo::anys::errors::any_handle_cast_error const &a_cast_error )
{
    a_os << "{ "
         << "code={" << a_cast_error.code() << "}"
         << " }";
    return a_os;
}

////////////////////////////////////////////////////////////////////////////////
}}// EONS SOLO::TESTING
////////////////////////////////////////////////////////////////////////////////
