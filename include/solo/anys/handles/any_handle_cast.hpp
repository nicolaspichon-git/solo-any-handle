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
namespace solo {
////////////////////////////////////////////////////////////////////////////////

// -- package:

/// @ingroup SoloAnyHandle
/// @brief The result type of the operation of casting a @em non-mutable @c any_handle handle.
template < typename T >
using any_handle_cast_result_type = anys::outcomes::any_handle_cast_result<T const, solo::mutability::false_>;

/// @ingroup SoloAnyHandle
/// @brief Cast the given @c any_handle to a typed shared pointer pointing to the @em non-mutable handled object.
/// @param a_handle The type-erased handle to cast.
/// @pre   @c T is the type stored in the given @c a_handle.
/// @post  <c>( result.has_value() && result.assume_value() == a_handle.pointer() ) || ( result.has_error() )</c>
/// @note  Ignore the mutability flag of the given @c a_handle since
/// casting to <c>T const</c> or <c>T</c> returns the same @c shared_ptr<T const> object:
///
/// @code
///
///     auto result1 = any_handle_cast<T const>(ah);
///     auto result2 = any_handle_cast<T>(ah);
///     assert(result1 == result2);
///     assert(std::is_same<decltype(result1), std::shared_ptr<T const>>::value);
///     assert(std::is_same<decltype(result2), std::shared_ptr<T const>>::value);
///
/// @endcode
///
/// This is due to the fact that @c typeid operator ignores cv-qualifiers (@c const, @c volatile).
///
template < typename T >
any_handle_cast_result_type<T> any_handle_cast( solo::any_handle const & ) noexcept;

//..............................................................................

// -- definition:

/// @ingroup SoloAnyHandle
template < typename T >
inline any_handle_cast_result_type<T>
any_handle_cast( solo::any_handle const &a_handle ) noexcept
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
    return std::static_pointer_cast<T const>(a_handle.pointer());// nothrow
}

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLO
////////////////////////////////////////////////////////////////////////////////
