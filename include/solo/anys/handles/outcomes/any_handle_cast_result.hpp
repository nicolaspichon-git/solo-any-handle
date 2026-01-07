//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/errors/any_handle_cast_error.hpp>
#include <solo/anys/handles/mutability.hpp>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace anys { namespace outcomes {
////////////////////////////////////////////////////////////////////////////////

/// @ingroup SoloAnyHandle
/// @brief The result of the non-throwing @c solo::any_handle_cast function.
/// @details May contains a shared pointer of type @c T as value, or an error object
/// of type @c solo::anys::errors::any_handle_cast_error if casting operation failed.
template < typename T, solo::mutability IsMutable >
class any_handle_cast_result
{
public:

    using value_type = std::shared_ptr<T>;

    static_assert(std::is_nothrow_default_constructible<value_type>::value, "");
    static_assert(std::is_nothrow_move_constructible<value_type>::value, "");
    static_assert(std::is_nothrow_move_assignable<value_type>::value, "");

    using error_type = anys::errors::any_handle_cast_error;

    static_assert(std::is_nothrow_default_constructible<error_type>::value, "");
    static_assert(std::is_nothrow_move_constructible<error_type>::value, "");
    static_assert(std::is_nothrow_move_assignable<error_type>::value, "");

    constexpr any_handle_cast_result( value_type &&a_value ) noexcept
        : m_value{std::move(a_value)}// nothrow
        , m_valuable{true}
    {}

    constexpr any_handle_cast_result( error_type &&a_error ) noexcept
        : m_error{std::move(a_error)}// nothrow
        , m_valuable{false}
    {}

    any_handle_cast_result() = delete;

    constexpr bool has_value() const noexcept
    {
        return m_valuable;
    }

    constexpr value_type const &assume_value() const & noexcept
    {
        return m_value;
    }

    constexpr value_type assume_move_value() && noexcept
    {
        auto output = value_type{std::move(m_value)};
        m_value = value_type{};
        return output;
    }

    constexpr bool has_error() const noexcept
    {
        return not m_valuable;
    }

    constexpr error_type const &assume_error() const & noexcept
    {
        return m_error;
    }

    constexpr error_type assume_move_error() && noexcept
    {
        auto output = error_type{std::move(m_error)};
        m_error = error_type{};
        return output;
    }

private:

    value_type m_value{};
    error_type m_error{};
    bool m_valuable{false};
};

////////////////////////////////////////////////////////////////////////////////
}}}// EONS SOLO::ANYS::OUTCOME
////////////////////////////////////////////////////////////////////////////////
