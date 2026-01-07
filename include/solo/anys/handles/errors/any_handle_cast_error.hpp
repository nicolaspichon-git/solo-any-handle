//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/errors/any_handle_cast_errc.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace anys { namespace errors {
////////////////////////////////////////////////////////////////////////////////

/// @ingroup SoloAnyHandle
/// @brief Store diagnostic information on @c any_handle casting operation failures.
/// @details This is the @c error type of the generic @c result type of @c any_handle casting operations.
/// @see @c any_handle_cast_result<T, IsMutable>.
/// @see @c any_handle_cast_errc.
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

////////////////////////////////////////////////////////////////////////////////
}}}// EONS SOLO::ANYS::ERRORS
////////////////////////////////////////////////////////////////////////////////
