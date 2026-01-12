//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/outcomes/any_handle_cast_result.hpp>
#include <solo/anys/handles/any_handle.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace obsolete {
////////////////////////////////////////////////////////////////////////////////

// -- package

/// @ingroup SoloAnyHandle
/// @brief The result type of the operation of casting a @em mutable @c any_handle handle.
template < typename T >
using any_handle_mutable_cast_result_type = anys::outcomes::any_handle_cast_result<T, solo::mutability::true_>;

/// @ingroup SoloAnyHandle
/// @brief Cast the given @c any_handle to a typed shared pointer pointing to the @em mutable handled object.
/// @param a_handle The type-erased handle to cast.
/// @pre   @c T is the type stored in @c a_handle.
/// @pre   @c a_handle is @em mutable (see @c any_handle).
/// @post  <c>( result.has_value() && result.assume_value() == a_handle.pointer() == a_handle.mutable_pointer() ) || ( result.has_arror() )</c>
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
any_handle_mutable_cast_result_type<T> any_handle_mutable_cast( solo::any_handle const & ) noexcept;

//..............................................................................

// -- definitions

/// @ingroup SoloAnyHandle
template< typename T >
inline any_handle_mutable_cast_result_type<T>
any_handle_mutable_cast( solo::any_handle const &a_handle ) noexcept
{
    using solo::anys::errors::any_handle_cast_error;

    if ( a_handle.empty() )// nothrow
    {
        return any_handle_cast_error{any_handle_cast_error::code_type::empty_source};// nothrow
    }
    if ( a_handle.type() != typeid(T) )// nothrow
    {
        return any_handle_cast_error{any_handle_cast_error::code_type::bad_source_type};// nothrow
    }
    if ( not a_handle.is_mutable() )// nothrow
    {
        return any_handle_cast_error{any_handle_cast_error::code_type::bad_source_mutability};// nothrow
    }

    return std::static_pointer_cast<T>(a_handle.mutable_pointer());// nothrow
}

////////////////////////////////////////////////////////////////////////////////
}}// EONS SOLO::OBS
////////////////////////////////////////////////////////////////////////////////
