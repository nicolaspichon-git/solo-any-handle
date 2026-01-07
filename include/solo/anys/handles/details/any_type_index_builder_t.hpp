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

#include <solo/anys/handles/any_type_index.hpp>
#include <solo/anys/handles/details/select_any_type_info_instance_t.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace anys { namespace details {
////////////////////////////////////////////////////////////////////////////////

// -- package :

template < typename T >
struct any_type_index_builder;

//..............................................................................
//..............................................................................

// -- definition :

/// @ingroup SoloAnyHandleDetail
/// @brief Build a <c>any_type_index</c>-based object from the given target type.
template < typename T >
struct any_type_index_builder : any_type_index
{
    any_type_index_builder( mutability a_ismutable )
        : any_type_index
          {
              anys::detail::select_any_type_info_instance_ptr<T>(a_ismutable)
          }
    {}
};

////////////////////////////////////////////////////////////////////////////////
}}}// EONS SOLO::ANYS::DETAILS
////////////////////////////////////////////////////////////////////////////////
