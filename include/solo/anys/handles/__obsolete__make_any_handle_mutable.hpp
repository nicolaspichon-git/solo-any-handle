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
namespace solo { namespace obsolete {
////////////////////////////////////////////////////////////////////////////////

// -- package :

/// @ingroup SoloAnyHandle
/// @brief Safely build a mutable @c any_handle object
/// from an already-built typed shared pointer to @em mutable @c T.
/// @pre @c T is a plain type (not a reference type, not cv-qualified).
/// @param a_shared_pointer_to_copy A shared pointer of type @c T to the mutable object to handle.
///
/// Example:
///
/// @code
///
///     auto x = std::make_shared<T>(...);
///     auto y = make_any_handle_mutable(x);
///     assert(y.pointer() == x);
///     assert(y.type() == typeid(T));
///     assert(y.is_mutable() == true);
///
/// @endcode
///
template< typename T >
any_handle make_any_handle_mutable( std::shared_ptr<T> const &a_shared_pointer_to_copy );

/// @ingroup SoloAnyHandle
/// @brief Specialize @c make_any_handle for type @c void (copying the input type-erased shared pointer).
/// @param a_type_erased_shared_pointer_to_copy A type-erased shared pointer to the mutable object to handle.
any_handle make_any_handle_mutable( std::shared_ptr<void> const &a_type_erased_shared_pointer_to_copy );

/// @ingroup SoloAnyHandle
/// @brief Specialize @c make_any_handle for type @c void (moving the input type-erased shared pointer).
/// @param a_type_erased_shared_pointer_to_move A type-erased shared pointer to the mutable object to handle.
any_handle make_any_handle_mutable( std::shared_ptr<void> &&a_type_erased_shared_pointer_to_move );

//..............................................................................
//..............................................................................

// -- definitions

/// @ingroup SoloAnyHandle
template< typename T >
inline any_handle 
make_any_handle_mutable( std::shared_ptr<T> const &a_shared_pointer_to_copy )
{
    static_assert(!std::is_reference<T>::value, "T should not be a reference type");
    static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value, "T should not be cv-qualified");
    return anys::details::any_handle_builder<T>( a_shared_pointer_to_copy, mutability::true_ );
}

/// @ingroup SoloAnyHandle
inline any_handle
make_any_handle_mutable( std::shared_ptr<void> const &a_type_erased_shared_pointer_to_copy )
{
    return anys::details::any_handle_builder<void>( a_type_erased_shared_pointer_to_copy, mutability::true_ );
}

/// @ingroup SoloAnyHandle
inline any_handle
make_any_handle_mutable( std::shared_ptr<void> &&a_type_erased_shared_pointer_to_move )
{
    return anys::details::any_handle_builder<void>( std::move(a_type_erased_shared_pointer_to_move), mutability::true_ );
}

////////////////////////////////////////////////////////////////////////////////
}}// EONS SOLO::OBS
////////////////////////////////////////////////////////////////////////////////
