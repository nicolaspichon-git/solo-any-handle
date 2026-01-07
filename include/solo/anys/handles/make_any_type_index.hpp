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

#include <solo/anys/handles/details/any_type_index_builder_t.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo {
////////////////////////////////////////////////////////////////////////////////

// -- package :

/// @ingroup SoloAnyHandle
/// @brief Templatized @c any_type_index factory.
/// @param a_ismutable  Which type of mutability should be associated with the type (non-mutable is the default).
/// @post Force the mutability flag to @c true if the given type @c T is @c const.
template < typename T >
any_type_index make_any_type_index( mutability a_ismutable = mutability::false_ ) noexcept;

//..............................................................................
//..............................................................................

// -- definition :

/// @ingroup SoloAnyHandle
template < typename T >
inline any_type_index
make_any_type_index( mutability a_ismutable ) noexcept
{
    return anys::details::any_type_index_builder<T>{a_ismutable};
}

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLO
////////////////////////////////////////////////////////////////////////////////
