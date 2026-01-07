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

#include <solo/anys/handles/details/any_handle_builder_t.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo {
////////////////////////////////////////////////////////////////////////////////

// -- package :

/// @ingroup SoloAnyHandle
/// @brief Safely build a non-mutable @c any_handle object
/// from an already-built typed shared pointer to @em non-mutable @c T.
/// @param a_shared_pointer_to_copy A shared pointer of type <c>const T</c> to the non-mutable object to handle.
///
/// Example:
///
/// @code
///
///     auto x = std::make_shared<const T>(...);
///     auto y = make_any_handle(x);
///     assert(y.type() == typeid(T));
///     assert(y.is_mutable() == false);
///     assert(y.pointer() == x);
///
/// @endcode
///
/// @note @c T can be @c const-qualified (since <c>const const T</c> automatically reduces to <c>const T</c>).
/// @note @c T is mechanically not a reference type (otherwise <c>const T</c> would have been undefined).
///
template< typename T >
any_handle make_any_handle( std::shared_ptr<const T> const &a_shared_pointer_to_copy );

/// @ingroup SoloAnyHandle
/// @brief Safely build a non-mutable @c any_handle object
/// from an already-built typed shared pointer to @em mutable @c T.
/// @pre @c T is a plain type (not a reference type and not cv-qualified).
/// @param a_shared_pointer_to_copy A shared pointer of type @c T to the non-mutable object to handle.
///
/// Example:
///
/// @code
///
///     auto x = std::make_shared<T>(...);
///     auto y = make_any_handle(x);
///     assert(y.type() == typeid(T));
///     assert(y.is_mutable() == false);
///     assert(y.pointer() == x);
///
/// @endcode
///
/// @note Although the given pointer points to a mutable object, the handled object is non-mutable (through the handle).
///
template< typename T >
any_handle make_any_handle( std::shared_ptr<T> const &a_shared_pointer_to_copy );

//..............................................................................
//..............................................................................

// -- implementation :

/// @ingroup SoloAnyHandle
template < typename T >
inline any_handle 
make_any_handle( std::shared_ptr<const T> const &a_shared_pointer_to_copy )
{
    static_assert(!std::is_reference<T>::value,"");
    return anys::detail::any_handle_builder<T>(a_shared_pointer_to_copy);
}

/// @ingroup SoloAnyHandle
template< typename T >
inline any_handle 
make_any_handle( std::shared_ptr<T> const &a_shared_pointer_to_copy )
{
    static_assert(!std::is_reference<T>::value, "T should not be a reference type");
    static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value, "T should not be cv-qualified");
    return anys::detail::any_handle_builder<T>{a_shared_pointer_to_copy, mutability::false_};
}

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLO
////////////////////////////////////////////////////////////////////////////////
