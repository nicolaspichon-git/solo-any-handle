//------------------------------------------------------------------------------
//
// Copyright (c) 2021 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/any_handle.hpp>
#include <solo/anys/handles/pragmas/disables_warnings.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo {
////////////////////////////////////////////////////////////////////////////////

// -- package :

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_handle objects.
///
/// The rationale is to compare pointers only,
/// ignoring type information, and acting as if @c any_handle objects
/// were raw pointers (as @c std::shared_ptr<T> do).
///
/// Users should use @c any_handle::equals method to perfom exact equality comparison
/// between @c any_handle objects.
///
inline bool operator==( any_handle const &, any_handle const & ) noexcept;
inline bool operator!=( any_handle const &, any_handle const & ) noexcept;
inline bool operator<=( any_handle const &, any_handle const & ) noexcept;
inline bool operator< ( any_handle const &, any_handle const & ) noexcept;
inline bool operator>=( any_handle const &, any_handle const & ) noexcept;
inline bool operator> ( any_handle const &, any_handle const & ) noexcept;

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_handle and @c std::shared_ptr<T> objects.
/// @see operator==( any_handle const &, any_handle const & )
/// @see operator!=( any_handle const &, any_handle const & )
/// @see operator<=( any_handle const &, any_handle const & )
/// @see operator< ( any_handle const &, any_handle const & )
/// @see operator>=( any_handle const &, any_handle const & )
/// @see operator> ( any_handle const &, any_handle const & )
template< typename T > bool operator==( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator!=( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator<=( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator< ( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator>=( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator> ( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator==( std::shared_ptr<T> const &, any_handle const & ) noexcept;
template< typename T > bool operator!=( std::shared_ptr<T> const &, any_handle const & ) noexcept;
template< typename T > bool operator<=( std::shared_ptr<T> const &, any_handle const & ) noexcept;
template< typename T > bool operator< ( std::shared_ptr<T> const &, any_handle const & ) noexcept;
template< typename T > bool operator>=( std::shared_ptr<T> const &, any_handle const & ) noexcept;
template< typename T > bool operator> ( std::shared_ptr<T> const &, any_handle const & ) noexcept;

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_handle object and raw pointer.
/// @see operator==( any_handle const &, any_handle const & )
/// @see operator!=( any_handle const &, any_handle const & )
/// @see operator<=( any_handle const &, any_handle const & )
/// @see operator< ( any_handle const &, any_handle const & )
/// @see operator>=( any_handle const &, any_handle const & )
/// @see operator> ( any_handle const &, any_handle const & )
inline bool operator==( any_handle const &, void const * ) noexcept;
inline bool operator!=( any_handle const &, void const * ) noexcept;
inline bool operator<=( any_handle const &, void const * ) noexcept;
inline bool operator< ( any_handle const &, void const * ) noexcept;
inline bool operator>=( any_handle const &, void const * ) noexcept;
inline bool operator> ( any_handle const &, void const * ) noexcept;
inline bool operator==( void const *, any_handle const & ) noexcept;
inline bool operator!=( void const *, any_handle const & ) noexcept;
inline bool operator<=( void const *, any_handle const & ) noexcept;
inline bool operator< ( void const *, any_handle const & ) noexcept;
inline bool operator>=( void const *, any_handle const & ) noexcept;
inline bool operator> ( void const *, any_handle const & ) noexcept;

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_handle object and @c nullptr.
/// @see operator==( any_handle const &, any_handle const & )
/// @see operator!=( any_handle const &, any_handle const & )
/// @see operator<=( any_handle const &, any_handle const & )
/// @see operator< ( any_handle const &, any_handle const & )
/// @see operator>=( any_handle const &, any_handle const & )
/// @see operator> ( any_handle const &, any_handle const & )
inline bool operator==( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator!=( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator<=( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator< ( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator>=( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator> ( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator==( std::nullptr_t, any_handle const & ) noexcept;
inline bool operator!=( std::nullptr_t, any_handle const & ) noexcept;
inline bool operator>=( std::nullptr_t, any_handle const & ) noexcept;
inline bool operator> ( std::nullptr_t, any_handle const & ) noexcept;
inline bool operator<=( std::nullptr_t, any_handle const & ) noexcept;
inline bool operator< ( std::nullptr_t, any_handle const & ) noexcept;

//..............................................................................
//..............................................................................

// -- definitions :

#define SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( op ) \
    inline bool operator op ( any_handle const &a_x, any_handle const &a_y ) noexcept \
    { \
        return a_x.pointer() op a_y.pointer(); \
    } \
    template< typename T > \
    inline bool operator op ( any_handle const &a_x, std::shared_ptr<T> const &a_y ) noexcept \
    { \
        return a_x.pointer() op a_y; \
    } \
    template< typename T > \
    inline bool operator op ( std::shared_ptr<T> const &a_x, any_handle const &a_y ) noexcept \
    { \
        return a_x op a_y.pointer(); \
    } \
    inline bool operator op ( any_handle const &a_x, void const *a_y ) noexcept \
    { \
        return a_x.pointer().get() op a_y; \
    } \
    inline bool operator op ( void const *a_x, any_handle const &a_y ) noexcept \
    { \
        return a_x op a_y.pointer().get(); \
    } \
    inline bool operator op ( any_handle const &a_x, std::nullptr_t ) noexcept \
    { \
        return a_x.pointer() op nullptr; \
    } \
    inline bool operator op ( std::nullptr_t, any_handle const &a_y ) noexcept \
    { \
        return nullptr op a_y.pointer(); \
    }

    SOLO_DISABLE_WARNING_PUSH
    SOLO_DISABLE_WARNING_UNREFERENCED_FUNCTION

    SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( == )
    SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( != )
    SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( < )
    SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( <= )
    SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( > )
    SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( >= )

    SOLO_DISABLE_WARNING_POP

#undef SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLO
////////////////////////////////////////////////////////////////////////////////
