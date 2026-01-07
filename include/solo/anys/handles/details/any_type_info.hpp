//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/mutability.hpp>
#include <typeindex>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace anys { namespace detail {
////////////////////////////////////////////////////////////////////////////////

// -- package :

struct any_type_info;

//..............................................................................
//..............................................................................

// -- definition :

/// @ingroup SoloAnyHandleDetail
/// @class any_type_info
/// @brief Wrap @c std::type_info runtime type information with additional
/// emptyness and mutability information.
struct any_type_info
{
    constexpr explicit any_type_info( std::type_index const &a_eti, mutability a_ismutable ) noexcept
        : m_external_type_index{ a_eti }// noexcept
        , m_mutable_flag{ mutability_as_boolean(a_ismutable) }
        , m_nonempty_flag{ true }
    {}

     any_type_info() noexcept
        : m_external_type_index{ typeid(void) }// noexcep
        , m_mutable_flag{ false }
        , m_nonempty_flag{ false }
    {}

    const std::type_index m_external_type_index;
    const bool m_mutable_flag;
    const bool m_nonempty_flag;
};

////////////////////////////////////////////////////////////////////////////////
}}}// EONS SOLO::ANYS::DETAIL
////////////////////////////////////////////////////////////////////////////////
