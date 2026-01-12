//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/any_handle_mutable_cast.hpp>
#include <solo/anys/handles/details/throw_any_handle_cast_exception_t.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace obsolete {
////////////////////////////////////////////////////////////////////////////////

// -- package :

/// @ingroup SoloAnyHandle
/// @brief Cast the given @c any_handle to a typed shared pointer pointing to the @em mutable handled object.
/// @param a_handle The type-erased handle to cast.
/// @pre   @c T is the type stored in @c a_handle.
/// @pre   @c a_handle is @em mutable (see @c any_handle).
/// @post  <c>result == a_handle.pointer() == a_handle.mutable_pointer()</c>
/// @throw Throw a @c bad_any_handle_cast exception if @c T is not the type stored in @c a_handle.
/// @throw Throw a @c bad_any_handle_cast exception if @c a_handle is not @em mutable (see @c any_handle).
/// @note  Casting to <c>T const</c> returns a @c std::shared_ptr<T const> object although the mutability flag is set :
///
/// @code
///
///     auto result1 = any_handle_mutable_cast<T const>(ah);
///     auto result2 = any_handle_cast<T>(ah);
///     assert(result1 == result2);
///     assert(typeid(result1) == typeid(result2));
///     assert(std::is_same<decltype(result1), std::shared_ptr<T const>::value);
///
/// @endcode
///
/// @note The given @c any_handle is passed as a const reference because,
/// whereas the handled object is mutable, the handle itself is not modified
/// by the casting. This is how _handles_ should work.
///
template< typename T >
std::shared_ptr<T> any_handle_mutable_cast_or_throw( any_handle const &a_handle );

//..............................................................................
//..............................................................................

// -- definitions

/// @ingroup SoloAnyHandle
template< typename T >
inline std::shared_ptr<T>
any_handle_mutable_cast_or_throw( any_handle const &a_handle )
{
    auto cr = any_handle_mutable_cast<T>(a_handle);
    if (cr.has_error())
    {
        anys::details::throw_any_handle_cast_exception<T const,mutability::true_>(a_handle);
        return nullptr;// unreachable
    }
    return std::move(cr).assume_move_value();
}

////////////////////////////////////////////////////////////////////////////////
}}// EONS SOLO::OBS
////////////////////////////////////////////////////////////////////////////////
