//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/details/any_type_info.hpp>
#include <experimental/memory>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace obsolete { namespace anys { namespace details {
////////////////////////////////////////////////////////////////////////////////

using solo::anys::details::any_type_info;

// -- package

template < typename T, mutability IsMutable >
std::experimental::observer_ptr<any_type_info const>
any_type_info_instance_ptr() noexcept;

//..............................................................................
//..............................................................................

// -- definitions

/// @ingroup SoloAnyHandleDetails
/// @brief Return a non-mutable reference to the static @c any_handle_info_wrapper
/// object associated with the template parameters.
/// @post Return a non-empty type wrapper.
template < typename T, mutability IsMutable = mutability::false_ >
inline std::experimental::observer_ptr<any_type_info const>
any_type_info_instance_ptr() noexcept
{
    // @c std::decay<T> : applies lvalue-to-rvalue, array-to-pointer, and function-to-pointer
    // implicit conversions to the type T, removes cv-qualifiers,
    // and defines the resulting type as the member typedef type.
    //
    // Formally:
    // - If T names the type "array of U" or "reference to array of U", the member typedef type is U*.
    // - If T is a function type F or a reference thereto, the member typedef type is @c std::add_pointer<F>::type.
    // - Otherwise, the member typedef type is @c std::remove_cv<std::remove_reference<T>::type>::type.
    static auto const sti = any_type_info{ typeid(T), IsMutable };
    return std::experimental::make_observer(&sti);
}

////////////////////////////////////////////////////////////////////////////////
}}}}// EONS SOLO::OBS::ANYS::DETAILS
////////////////////////////////////////////////////////////////////////////////
