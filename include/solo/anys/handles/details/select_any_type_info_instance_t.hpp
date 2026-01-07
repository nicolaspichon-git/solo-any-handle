//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/details/any_type_info_instance_t.hpp>

// already included: #include <experimental/memory>
//Clazy: does not used direcly: #include <type_traits>
//Clazy: does not used direcly: #include <typeindex>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace anys { namespace detail {
////////////////////////////////////////////////////////////////////////////////

// -- package:

template < typename T >
std::experimental::observer_ptr<any_type_info const>
select_any_type_info_instance_ptr( mutability a_ismutable ) noexcept;

//..............................................................................
//..............................................................................

// -- definition :

/// @ingroup SoloAnyHandleDetail
/// @brief Select the static @c any_handle_info_wrapper matching the given mutability flag.
/// @param a_ismutable The mutability selector.
/// @post Return a non-empty type wrapper
/// @post @c T is @c const ==> return @c any_type_info_instance_of<T,false>()
/// @post @c T is not @c const and @c mutable_flag_ is @c false ==> return @c any_type_info_instance_of<T,false>()
/// @post @c T is not @c const and @c mutable_flag_ is @c true ==> return @c any_type_info_instance_of<T,true>()
template < typename T >
inline std::experimental::observer_ptr<any_type_info const>
select_any_type_info_instance_ptr( mutability a_ismutable ) noexcept
{
    return ( ( a_ismutable == mutability::true_ ) && !( std::is_const<T>::value ) ) ?
            any_type_info_instance_ptr<T,mutability::true_>() :
            any_type_info_instance_ptr<T,mutability::false_>();
}

////////////////////////////////////////////////////////////////////////////////
}}}// EONS SOLO::ANYS::DETAIL
////////////////////////////////////////////////////////////////////////////////
