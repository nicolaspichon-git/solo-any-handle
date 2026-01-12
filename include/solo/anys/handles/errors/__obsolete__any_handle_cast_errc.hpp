//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <cstdint>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace anys { namespace errors {
////////////////////////////////////////////////////////////////////////////////

/// @ingroup SoloAnyHandle
/// @brief The reason why a @c any_handle casting operation could failed.
/// @see @c any_handle_cast_error.
enum class any_handle_cast_errc: std::int8_t
{
    undefined = 0,
    empty_source,
    bad_source_type,
    bad_source_mutability
};

////////////////////////////////////////////////////////////////////////////////
}}}// EONS SOLO::ANYS::ERRORS
////////////////////////////////////////////////////////////////////////////////
