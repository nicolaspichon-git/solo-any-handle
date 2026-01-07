//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/any_handle_cast.hpp>
#include <solo/anys/handles/details/throw_any_handle_cast_exception_t.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo {
////////////////////////////////////////////////////////////////////////////////

// -- package:

/// @ingroup SoloAnyHandle
/// @brief Cast the given @c any_handle to a typed shared pointer pointing to the @em non-mutable handled object.
/// @param a_handle The type-erased handle to cast.
/// @pre   @c T is the type stored in @c a_handle.
/// @post  <c>result == a_handle.pointer()</c>
/// @throw Throw a @c solo::anys::exceptions::bad_any_handle_cast exception if @c T is not the type stored in the given @c a_handle.
/// @note  Ignore the mutability flag of the given @c a_handle.
/// @note  Casting to <c>T const</c> or <c>T</c> returns the same @c shared_ptr<T const> object:
///
/// @code
///
///     auto result1 = any_handle_cast_or_throw<T const>(ah);
///     auto result2 = any_handle_cast_or_throw<T>(ah);
///     assert(result1 == result2);
///     assert(std::is_same<decltype(result1), std::shared_ptr<T const>>::value);
///     assert(std::is_same<decltype(result2), std::shared_ptr<T const>>::value);
///
/// @endcode
///
/// This is due to the fact that @c typeid operator ignores cv-qualifiers (@c const, @c volatile).
///
template< typename T >
std::shared_ptr<T const> any_handle_cast_or_throw( any_handle const & );

//..............................................................................
//..............................................................................

// -- definition:

/// @ingroup SoloAnyHandle
template< typename T >
inline std::shared_ptr<T const>
any_handle_cast_or_throw( any_handle const &a_handle )
{
    auto cr = any_handle_cast<T>(a_handle);
    if (cr.has_error())
    {
        anys::detail::throw_any_handle_cast_exception<T const,mutability::false_>(a_handle);
        return nullptr;// unreachable
    }
    return std::move(cr).assume_move_value();
}

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLO
////////////////////////////////////////////////////////////////////////////////
