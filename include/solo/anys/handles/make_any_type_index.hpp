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

////////////////////////////////////////////////////////////////////////////////
namespace solo {
////////////////////////////////////////////////////////////////////////////////

// -- packages

/// @ingroup SoloAnyHandle
/// @brief Templatized @c any_type_index factory.
/// @param a_ismutable  Which type of mutability should be associated with the type (non-mutable is the default).
/// @post Force the mutability flag to @c true if the given type @c T is @c const.
template < typename T >
any_type_index make_any_type_index( mutability a_ismutable = mutability::false_ ) noexcept;

//..............................................................................
//..............................................................................

// -- definitions

namespace anys { namespace details {

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

    // -- definitions

    /// @ingroup SoloAnyHandleDetails
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
                   any_type_info_instance_ptr<T, mutability::true_>() :
                   any_type_info_instance_ptr<T, mutability::false_>();
    }

    // -- definitions

    /// @ingroup SoloAnyHandleDetails
    /// @brief Build a <c>any_type_index</c>-based object from the given target type.
    template < typename T >
    struct any_type_index_builder : any_type_index
    {
        any_type_index_builder( mutability a_ismutable )
            : any_type_index
              {
                  anys::details::select_any_type_info_instance_ptr<T>(a_ismutable)
              }
        {}
    };

}}// EONS ANYS::DETAILS

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
