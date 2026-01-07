    //------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/any_handle.hpp>

#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace anys { namespace exceptions {
////////////////////////////////////////////////////////////////////////////////

// -- package :

class bad_any_handle_cast;

//..............................................................................
//..............................................................................

// -- implementation :

/// @ingroup SoloAnyHandle
/// @brief The exception thrown by @c any_handle_cast functions on a failed casting operation.
class bad_any_handle_cast
        : public std::runtime_error
{
public:

    struct cast_info
    {
        std::type_index type;
        bool mutability;
    };

    /// @brief Explicit member-based constructor.
    /// @param a_failing_handle The @c any_handle object that falied to cast.
    /// @param a_expected_type The type index of the excepted type (the casting target type).
    /// @param a_expected_mutability The excepted mutability type (the casting target mutability).
    /// @see <c>any_handle_cast_or_throw</c>, <c>any_handle_mutable_cast_or_throw</c>.
    ///
    /// Example:
    ///
	///	@code
    ///     throw bad_any_handle_cast
    ///     {
    ///         the_given_any_handle, typeid(TheGivenTypeToCastTo), the_mutability_casting_operation
    ///     };
	///	@endcode
    ///
    bad_any_handle_cast
    (
        any_handle      const &a_failing_handle,
        std::type_index const &a_expected_type,
        mutability             a_expected_mutability
    )
        : std::runtime_error("bad any handle cast")
        , m_actual { cast_info{ a_failing_handle.type(), a_failing_handle.is_mutable()} }
        , m_expected{ cast_info{ a_expected_type, mutability_as_boolean(a_expected_mutability)} }
    {}

    /// @brief The actual type information (the type the failing @c any_handle object has).
    constexpr cast_info const &actual() const noexcept
    {
        return m_actual;
    };

    /// @brief The expected type (what the caller provided).
    constexpr cast_info const &expected() const noexcept
    {
        return m_expected;
    }

private:

    cast_info m_actual;
    cast_info m_expected;
};

////////////////////////////////////////////////////////////////////////////////
}}}// EONS SOLO::ANYS::EXCEPTIONS
////////////////////////////////////////////////////////////////////////////////
