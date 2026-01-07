//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

////////////////////////////////////////////////////////////////////////////////
namespace solo {
///////////////////////////////////////////////////////////////////////////////

// -- FWD DECLARATIONS :

enum class mutability : bool;
constexpr bool mutability_as_boolean(mutability a_mutability_value) noexcept;

//..............................................................................

/// @ingroup SoloAnyHandle
/// @brief Strong boolean mutability type.
enum class mutability : bool
{
    true_  = true,
    false_ = false
};

//..............................................................................

/// @ingroup SoloAnyHandle
/// @brief Convert a mutablity item to its underlying boolean value.
inline constexpr bool mutability_as_boolean(mutability a_mutability_value) noexcept
{
    return static_cast<bool>(a_mutability_value);
}

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLO
////////////////////////////////////////////////////////////////////////////////
