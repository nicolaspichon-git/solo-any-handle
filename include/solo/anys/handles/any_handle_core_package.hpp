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

/// @defgroup SoloAnyHandle Solo AnyHandle Library
/// @ingroup SoloCore
/// @brief @c solo::any_handle is a type-erased wrapper around @c std::shared_ptr<void>.
///
/// Main library components :
///
/// - @c class solo::any_handle
/// - @c template < typename... Args > any_handle solo::make_any_handle(args...)
/// - @c template < typename... Args > any_handle solo::make_any_handle_mutable(args...)
/// - @c template < typename TargetType > any_handle_cast_result_type<T> solo::cast_any_handle(any_handle)
/// - @c template < typename TargetType > any_handle_cast_mutable_result_type<T> solo::cast_any_handle_mutable(any_handle)
/// - @c template < typename T, mutability IsMutable > class solo::anys::outcome::any_handle_cast_result
/// - @c class solo::anys::errors::any_handle_cast_error
/// - @c template < typename TargetType > std::shared_ptr<T const> solo::cast_any_handle_or_throw(any_handle)
/// - @c template < typename TargetType > std::shared_ptr<T> solo::cast_any_handle_mutable_or_throw(any_handle)
/// - @c class solo::anys::exceptions::bad_any_handle_cast
/// - @c solo::any_type_index
/// - @c template < typename... Args> solo::make_any_type_index(args...)
///
/// @note @c solo::make_any_handle and @c solo::make_any_handle_mutable usually
/// cannot @em move the given @c std::shared_ptr<T> pointer because they have to
/// cast this pointer to @c std::shared_ptr<void>. Hence, these methods are
/// usually forced to create a copy of the given shared pointer.
/// The only case where a move is allowed is the case where a
/// @c std::shared_ptr<void> is given to @c solo::make_any_handle_mutable.

/// @defgroup SoloAnyHandleDetail AnyHandle Implementation Details
/// @ingroup SoloAnyHandle

//..............................................................................

#include <solo/anys/handles/any_handle_library_version.hpp>

// any type index :
// already included : #include <solo/anys/handles/any_type_index.hpp>
// already included : #include <solo/anys/handles/make_any_type_index.hpp>
#include <solo/anys/handles/any_type_index_comparison_operators.hpp>

// any handle :
// already included : #include <solo/anys/handles/any_handle.hpp>
#include <solo/anys/handles/any_handle_comparison_operators.hpp>

// factories :
#include <solo/anys/handles/make_any_handle.hpp>
#include <solo/anys/handles/make_any_handle_mutable.hpp>

// non-throwing casting :
#include <solo/anys/handles/any_handle_cast.hpp>
#include <solo/anys/handles/any_handle_mutable_cast.hpp>

// non-throwing casting error helpers :
#include <solo/anys/handles/errors/any_handle_cast_error_helpers.hpp>

// throwing casting :
// already included : #include <solo/anys/handles/Exceptions/bad_any_handle_cast.h>
#include <solo/anys/handles/any_handle_cast_or_throw.hpp>
#include <solo/anys/handles/any_handle_mutable_cast_or_throw.hpp>

////////////////////////////////////////////////////////////////////////////////
