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

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace anys { namespace errors {
////////////////////////////////////////////////////////////////////////////////

/// @ingroup SoloAnyHandle
/// @brief Check if the given casting error is due to an empty source.
inline constexpr bool is_empty_source_error(any_handle_cast_error const &a_error)
{
    return a_error.code() == any_handle_cast_errc::empty_source;
}

/// @ingroup SoloAnyHandle
/// @brief Check if the given casting error is due to a bad source type.
inline constexpr bool is_bad_source_type_error(any_handle_cast_error const &a_error)
{
    return a_error.code() == any_handle_cast_errc::bad_source_type;
}

/// @ingroup SoloAnyHandle
/// @brief Check if the given casting error is due to a bad source mutability.
inline constexpr bool is_bad_source_mutability_error(any_handle_cast_error const &a_error)
{
    return a_error.code() == any_handle_cast_errc::bad_source_mutability;
}

////////////////////////////////////////////////////////////////////////////////
}}}// EONS SOLO::ANYS::ERRORS
////////////////////////////////////////////////////////////////////////////////
