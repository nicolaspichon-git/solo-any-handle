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

#include <solo/anys/handles/any_type_index.hpp>
#include <solo/anys/handles/pragmas/disables_warnings.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace obsolete {
////////////////////////////////////////////////////////////////////////////////

// -- package

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_type_index objects.
///
/// The rationale is to compare builtin c++ type information only,
/// ignoring emtyness and mutablity flag, and acting as if @c any_type_index objects
///  were @c std::type_info objects.
///
/// Users should use @c any_type_index::equals method to perfom exact equality comparison
/// between @c any_type_index objects.
///
bool operator==( any_type_index const &, any_type_index const & ) noexcept;
bool operator!=( any_type_index const &, any_type_index const & ) noexcept;
bool operator<=( any_type_index const &, any_type_index const & ) noexcept;
bool operator< ( any_type_index const &, any_type_index const & ) noexcept;
bool operator>=( any_type_index const &, any_type_index const & ) noexcept;
bool operator> ( any_type_index const &, any_type_index const & ) noexcept;

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_type_index and @c std::type_index objects.
/// @see operator==( any_type_index const &, any_type_index const & )
/// @see operator!=( any_type_index const &, any_type_index const & )
/// @see operator<=( any_type_index const &, any_type_index const & )
/// @see operator< ( any_type_index const &, any_type_index const & )
/// @see operator>=( any_type_index const &, any_type_index const & )
/// @see operator> ( any_type_index const &, any_type_index const & )
bool operator==( any_type_index const &, std::type_index const & ) noexcept;
bool operator!=( any_type_index const &, std::type_index const & ) noexcept;
bool operator<=( any_type_index const &, std::type_index const & ) noexcept;
bool operator< ( any_type_index const &, std::type_index const & ) noexcept;
bool operator>=( any_type_index const &, std::type_index const & ) noexcept;
bool operator> ( any_type_index const &, std::type_index const & ) noexcept;
bool operator==( std::type_index const &, any_type_index const & ) noexcept;
bool operator!=( std::type_index const &, any_type_index const & ) noexcept;
bool operator<=( std::type_index const &, any_type_index const & ) noexcept;
bool operator< ( std::type_index const &, any_type_index const & ) noexcept;
bool operator>=( std::type_index const &, any_type_index const & ) noexcept;
bool operator> ( std::type_index const &, any_type_index const & ) noexcept;


/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_type_index and @c std::type_info objects.
/// @see operator==( any_type_index const &, any_type_index const & )
/// @see operator!=( any_type_index const &, any_type_index const & )
/// @see operator<=( any_type_index const &, any_type_index const & )
/// @see operator< ( any_type_index const &, any_type_index const & )
/// @see operator>=( any_type_index const &, any_type_index const & )
/// @see operator> ( any_type_index const &, any_type_index const & )
bool operator==( any_type_index const &, std::type_info const & ) noexcept;
bool operator!=( any_type_index const &, std::type_info const & ) noexcept;
bool operator<=( any_type_index const &, std::type_info const & ) noexcept;
bool operator< ( any_type_index const &, std::type_info const & ) noexcept;
bool operator>=( any_type_index const &, std::type_info const & ) noexcept;
bool operator> ( any_type_index const &, std::type_info const & ) noexcept;
bool operator==( std::type_info const &, any_type_index const & ) noexcept;
bool operator!=( std::type_info const &, any_type_index const & ) noexcept;
bool operator<=( std::type_info const &, any_type_index const & ) noexcept;
bool operator< ( std::type_info const &, any_type_index const & ) noexcept;
bool operator>=( std::type_info const &, any_type_index const & ) noexcept;
bool operator> ( std::type_info const &, any_type_index const & ) noexcept;

//..............................................................................
//..............................................................................

// -- definitions

namespace
{
    inline bool operator==( std::type_info const &a_x, std::type_index const &a_y ) noexcept
    {
        return a_y == a_x;
    }

    inline bool operator!=( std::type_info const &a_x, std::type_index const &a_y ) noexcept
    {
        return a_y != a_x;
    }

    inline bool operator<=( std::type_info const &a_x, std::type_index const &a_y ) noexcept
    {
        return a_y <= a_x;
    }

    inline bool operator< ( std::type_info const &a_x, std::type_index const &a_y ) noexcept
    {
        return a_y <  a_x;
    }

    inline bool operator>=( std::type_info const &a_x, std::type_index const &a_y ) noexcept
    {
        return a_y >= a_x;
    }

    inline bool operator> ( std::type_info const &a_x, std::type_index const &a_y ) noexcept
    {
        return a_y >  a_x;
    }
}

#define SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( op ) \
    inline bool operator op ( any_type_index const &a_x, any_type_index const &a_y ) noexcept \
    { \
        return a_x.external_type_index() op a_y.external_type_index(); \
    } \
    inline bool operator op ( any_type_index const &a_x, std::type_index const &a_y ) noexcept \
    { \
        return a_x.external_type_index() op a_y; \
    } \
    inline bool operator op ( std::type_index const &a_x, any_type_index const &a_y ) noexcept \
    { \
        return a_x op a_y.external_type_index(); \
    } \
    inline bool operator op ( any_type_index const &a_x, std::type_info const &a_y ) noexcept \
    { \
        return a_x.external_type_index() op a_y; \
    } \
    inline bool operator op ( std::type_info const &a_x, any_type_index const &a_y ) noexcept \
    { \
        return a_x op a_y.external_type_index(); \
    }

    SOLO_DISABLE_WARNING_PUSH
    SOLO_DISABLE_WARNING_UNREFERENCED_FUNCTION

    SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( == )
    SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( != )
    SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( < )
    SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( <= )
    SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( > )
    SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( >= )

    SOLO_DISABLE_WARNING_POP

#undef SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR

////////////////////////////////////////////////////////////////////////////////
}}// EONS SOLO::OBS
////////////////////////////////////////////////////////////////////////////////
