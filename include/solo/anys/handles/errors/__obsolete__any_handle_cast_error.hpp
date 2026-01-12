//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <cstdint> // for any_handle_cast_errc

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace obsolete { namespace anys { namespace errors {
////////////////////////////////////////////////////////////////////////////////

// -- package

// .... main error classes

/// @ingroup SoloAnyHandle
/// @brief Store diagnostic information on @c any_handle casting operation failures.
/// @details This is the @c error type of the generic @c result type of @c any_handle casting operations.
/// @see @c any_handle_cast_result<T, IsMutable>.
/// @see @c any_handle_cast_errc.
class any_handle_cast_error;

// .... integral error codes

/// @ingroup SoloAnyHandle
/// @brief The reason why a @c any_handle casting operation could failed.
/// @see @c any_handle_cast_error.
enum class any_handle_cast_errc: std::int8_t;

// .... error diagnosis helpers

/// @ingroup SoloAnyHandle
/// @brief Check if the given casting error is due to an empty source.
constexpr bool is_empty_source_error(any_handle_cast_error const &a_error);

/// @ingroup SoloAnyHandle
/// @brief Check if the given casting error is due to a bad source type.
constexpr bool is_bad_source_type_error(any_handle_cast_error const &a_error);

/// @ingroup SoloAnyHandle
/// @brief Check if the given casting error is due to a bad source mutability.
constexpr bool is_bad_source_mutability_error(any_handle_cast_error const &a_error);

//..............................................................................
//..............................................................................

// -- definitions

/// @ingroup SoloAnyHandle
enum class any_handle_cast_errc: std::int8_t
{
    undefined = 0,
    empty_source,
    bad_source_type,
    bad_source_mutability
};

//..............................................................................

/// @ingroup SoloAnyHandle
class any_handle_cast_error
{
public:

    using code_type = any_handle_cast_errc;

    constexpr explicit any_handle_cast_error(code_type a_code) noexcept
       : m_code{a_code}
    {}

    constexpr explicit any_handle_cast_error() noexcept
       : m_code{code_type::undefined}
    {}

    constexpr code_type code() const noexcept
    {
        return m_code;
    }

private:

    code_type m_code;
};

//..............................................................................


/// @ingroup SoloAnyHandle
inline constexpr bool is_empty_source_error(any_handle_cast_error const &a_error)
{
    return a_error.code() == any_handle_cast_errc::empty_source;
}


/// @ingroup SoloAnyHandle
inline constexpr bool is_bad_source_type_error(any_handle_cast_error const &a_error)
{
    return a_error.code() == any_handle_cast_errc::bad_source_type;
}


/// @ingroup SoloAnyHandle
inline constexpr bool is_bad_source_mutability_error(any_handle_cast_error const &a_error)
{
    return a_error.code() == any_handle_cast_errc::bad_source_mutability;
}

////////////////////////////////////////////////////////////////////////////////
}}}}// EONS SOLO::OBS::ANYS::ERRORS
////////////////////////////////////////////////////////////////////////////////
