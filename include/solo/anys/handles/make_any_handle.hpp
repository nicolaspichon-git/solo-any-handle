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

#include <solo/anys/handles/make_any_type_index.hpp>
#include <solo/anys/handles/any_handle.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo {
////////////////////////////////////////////////////////////////////////////////

// -- package

// .... non-mutable any_handle factories

/// @ingroup SoloAnyHandle
/// @brief Safely build a non-mutable @c any_handle object
/// from an already-built typed shared pointer to @em non-mutable @c T.
/// @param a_shared_pointer_to_copy A shared pointer of type <c>const T</c> to the non-mutable object to handle.
///
/// Example:
///
/// @code
///
///     auto x = std::make_shared<const T>(...);
///     auto y = make_any_handle(x);
///     assert(y.type() == typeid(T));
///     assert(y.is_mutable() == false);
///     assert(y.pointer() == x);
///
/// @endcode
///
/// @note @c T can be @c const-qualified (since <c>const const T</c> automatically reduces to <c>const T</c>).
/// @note @c T is mechanically not a reference type (otherwise <c>const T</c> would have been undefined).
///
template< typename T >
any_handle make_any_handle( std::shared_ptr<const T> const &a_shared_pointer_to_copy );

/// @ingroup SoloAnyHandle
/// @brief Safely build a non-mutable @c any_handle object
/// from an already-built typed shared pointer to @em mutable @c T.
/// @pre @c T is a plain type (not a reference type and not cv-qualified).
/// @param a_shared_pointer_to_copy A shared pointer of type @c T to the non-mutable object to handle.
///
/// Example:
///
/// @code
///
///     auto x = std::make_shared<T>(...);
///     auto y = make_any_handle(x);
///     assert(y.type() == typeid(T));
///     assert(y.is_mutable() == false);
///     assert(y.pointer() == x);
///
/// @endcode
///
/// @note Although the given pointer points to a mutable object, the handled object is non-mutable (through the handle).
///
template< typename T >
any_handle make_any_handle( std::shared_ptr<T> const &a_shared_pointer_to_copy );

// .... mutable any_handle factories

/// @ingroup SoloAnyHandle
/// @brief Safely build a mutable @c any_handle object
/// from an already-built typed shared pointer to @em mutable @c T.
/// @pre @c T is a plain type (not a reference type, not cv-qualified).
/// @param a_shared_pointer_to_copy A shared pointer of type @c T to the mutable object to handle.
///
/// Example:
///
/// @code
///
///     auto x = std::make_shared<T>(...);
///     auto y = make_any_handle_mutable(x);
///     assert(y.pointer() == x);
///     assert(y.type() == typeid(T));
///     assert(y.is_mutable() == true);
///
/// @endcode
///
template< typename T >
any_handle make_any_handle_mutable( std::shared_ptr<T> const &a_shared_pointer_to_copy );

/// @ingroup SoloAnyHandle
/// @brief Specialize @c make_any_handle for type @c void (copying the input type-erased shared pointer).
/// @param a_type_erased_shared_pointer_to_copy A type-erased shared pointer to the mutable object to handle.
any_handle make_any_handle_mutable( std::shared_ptr<void> const &a_type_erased_shared_pointer_to_copy );

/// @ingroup SoloAnyHandle
/// @brief Specialize @c make_any_handle for type @c void (moving the input type-erased shared pointer).
/// @param a_type_erased_shared_pointer_to_move A type-erased shared pointer to the mutable object to handle.
any_handle make_any_handle_mutable( std::shared_ptr<void> &&a_type_erased_shared_pointer_to_move );

//..............................................................................
//..............................................................................

// -- definitions

namespace anys { namespace details {

    // /// @ingroup SoloAnyHandleDetails
    // /// @brief Select the static @c any_handle_info_wrapper matching the given mutability flag.
    // /// @param a_ismutable The mutability selector.
    // /// @post Return a non-empty type wrapper
    // /// @post @c T is @c const ==> return @c any_type_info_instance_of<T,false>()
    // /// @post @c T is not @c const and @c mutable_flag_ is @c false ==> return @c any_type_info_instance_of<T,false>()
    // /// @post @c T is not @c const and @c mutable_flag_ is @c true ==> return @c any_type_info_instance_of<T,true>()
    // template < typename T >
    // inline std::experimental::observer_ptr<any_type_info const>
    // select_any_type_info_instance_ptr( mutability a_ismutable ) noexcept
    // {
    //     return ( ( a_ismutable == mutability::true_ ) && !( std::is_const<T>::value ) ) ?
    //                any_type_info_instance_ptr<T,mutability::true_>() :
    //                any_type_info_instance_ptr<T,mutability::false_>();
    // }

    // /// @ingroup SoloAnyHandleDetails
    // /// @brief Build a <c>any_type_index</c>-based object from the given target type.
    // template < typename T >
    // struct any_type_index_builder : any_type_index
    // {
    //     any_type_index_builder( mutability a_ismutable )
    //         : any_type_index
    //           {
    //               anys::details::select_any_type_info_instance_ptr<T>(a_ismutable)
    //           }
    //     {}
    // };

    /// @ingroup SoloAnyHandleDetails
    /// @brief An helper class to safely build an @c any_handle object
    /// from an already-built typed shared pointer.
    ///
    /// Used by @c make_any_handle factory functions.
    ///
    /// @see @c make_any_handle, @c make_any_handle_mutable
    ///
    /// @note We dont need to overload @c any_handle_builder constructors to move the given shared pointer
    /// because the given shared pointer is @em always copied (through the cast operations to @c std::shared_ptr<void> ).
    ///
    template< typename T >
    struct any_handle_builder
            : public any_handle
    {
        /// @brief The underlying @c any_handle target type.
        ///
        /// The underlying @c any_handle target type is the plain version of the template parameter @c T (no reference, no cv-qualifier).
        /// The built @c any_handle object stores type information based on @c value_type type.
        /// @note A reference type cannot be cv-qualified.
        using value_type = std::remove_cv_t<std::remove_reference_t<T>>;

        /// @brief Check that this builder type can build a mutable handle.
        using is_mutable_type = std::integral_constant<bool,!std::is_const<std::remove_reference_t<T>>::value>;

        /// @brief Check that @c U type can build a shared pointer object convertible to @c std::shared_ptr<value_type> .
        template < typename U >
        using is_type_constructive = std::integral_constant<bool,
               !std::is_reference<U>::value
            && !std::is_volatile<U>::value
            && !std::is_const<U>::value
            && std::is_convertible<U*,value_type*>::value
        >;

        /// @brief SFINAE helper.
        template < typename U >
        using enable_if_type_is_constructive_t = std::enable_if_t<
            is_type_constructive<U>::value,
            struct type_is_constructive
        >;

        /// @brief SFINAE helper.
        template < typename U >
        using enable_mutable_if_type_is_constructive_t = std::enable_if_t<
            is_mutable_type::value && is_type_constructive<U>::value,
            struct type_is_constructive
        >;

        /// @brief Safely build a non-mutable @c any_handle object on an object of type @c value_type,
        /// copying an already-built typed shared pointer to a @em non-mutable object of type @c U,
        /// where @c U* is convertible to @c value_type* .
        /// @param a_sp A shared pointer of type <c>const U</c> to the non-mutable object to handle.
        /// @pre @c U is a plain type (not a reference and not cv-qualified) and @c U* is convertible to @c value_type*.
        /// @note The resulting @c any_handle object stores the type information based on @c value_type, not @c U.
        ///
        /// Example:
        ///
        /// @code
        ///
        ///     // Build a non-mutable any_handle object castable to type std::shared_ptr<const Base> :
        ///
        ///     class Base {};
        ///     class Derived : public Base {};
        ///     auto sp = std::make_shared<const Derived>(...);
        ///     auto result = any_handle_builder<Base>(sp);// <-- or any_handle_builder<const Base>
        ///     assert(result.type() == typeid(Base));
        ///     assert(result.is_mutable() == false);
        ///     auto sp2 = any_handle_cast<const Base>(result);// <-- could be any_handle_cast<Base>
        ///     static_assert(std::is_same_v<decltype(sp2),std::shared_ptr<const Base>>);
        ///
        /// @endcode
        ///
        template < typename U,
                   typename Enable = enable_if_type_is_constructive_t<U> >
        any_handle_builder( std::shared_ptr<const U> const &a_sp )
            : any_handle
            {
                make_any_type_index<value_type>(mutability::false_), // the type we want to store (with non-mutable flag)
                std::move(std::const_pointer_cast<void>(std::static_pointer_cast<const void>(a_sp)))// move the temporary
            }
        {}

        /// @brief Safely build an @c any_handle object on an object of type @c value_type,
        /// copying an already-built typed shared pointer to a @em mutable object of type @c U,
        /// where @c U* is convertible to @c value_type* .
        /// @param a_sp A shared pointer of type @c U to the object to handle.
        /// @param a_ismutable The desired mutability of the handled object.
        /// @pre U* must be convertible to @c value_type*.
        /// @note The resulting @c any_handle object stores the type information based on @c value_type, not @c U.
        ///
        /// Example:
        ///
        /// @code
        ///
        ///     // Build a non-mutable any_handle object castable to type std::shared_ptr<const Base> :
        ///
        ///     class Base {};
        ///     class Derived : public Base {};
        ///     auto sp = std::make_shared<Derived>(...);// <-- must be mutable, even if the mutability value is false
        ///     auto result = any_handle_builder<Base>(sp, mutability::false_);// <-- cannot be any_handle_builder<const Base>
        ///     assert(result.type() == typeid(Base));
        ///     assert(result.is_mutable() == false);
        ///     auto result_value = any_handle_cast<const Base>(result);// <-- could be any_handle_cast<Base>
        ///     static_assert(std::is_same_v<decltype(result_value),std::shared_ptr<const Base>>);
        ///
        ///     // Build a mutable any_handle object castable to type std::shared_ptr<Base> :
        ///
        ///     auto result_m = any_handle_builder<Base>(sp_m, mutability::true_);// <-- cannot be any_handle_builder<const Base>
        ///     assert(result_m.type() == typeid(Base));
        ///     assert(result_m.is_mutable() == true);
        ///     auto result_m_value_m = any_handle_mutable_cast<Base>(result_m);// <-- cannot be any_handle_mutable_cast<const Base>
        ///     static_assert(std::is_same_v<decltype(result_m_value_m),std::shared_ptr<Base>>);
        ///
        /// @endcode
        ///
        template < typename U,
                   typename Enable = enable_mutable_if_type_is_constructive_t<U> >
        any_handle_builder( std::shared_ptr<U> const &a_sp, mutability a_ismutable )
            : any_handle
            {
                make_any_type_index<value_type>(a_ismutable), // the type we want to store (with the given mutability flag)
                std::move(std::static_pointer_cast<void>(a_sp))// move the temporary
            }
        {}
    };

    //..............................................................................

    /// @ingroup SoloAnyHandleDetails
    /// @brief Specialize @c any_handle_builder for type @c void .
    template <>
    struct any_handle_builder<void>
            : public any_handle
    {
        any_handle_builder( std::shared_ptr<void> const &sp, mutability ismutable )
            : any_handle{ make_any_type_index<void>(ismutable), sp}
        {}

        any_handle_builder( std::shared_ptr<void> &&sp, mutability ismutable )
            : any_handle{ make_any_type_index<void>(ismutable), std::move(sp)}
        {}
    };

}}// EONS ANYS::DETAILS

// -- definitions

/// @ingroup SoloAnyHandle
template < typename T >
inline any_handle 
make_any_handle( std::shared_ptr<const T> const &a_shared_pointer_to_copy )
{
    static_assert(!std::is_reference<T>::value,"");
    return anys::details::any_handle_builder<T>(a_shared_pointer_to_copy);
}

/// @ingroup SoloAnyHandle
template< typename T >
inline any_handle 
make_any_handle( std::shared_ptr<T> const &a_shared_pointer_to_copy )
{
    static_assert(!std::is_reference<T>::value, "T should not be a reference type");
    static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value, "T should not be cv-qualified");
    return anys::details::any_handle_builder<T>{a_shared_pointer_to_copy, mutability::false_};
}

//..............................................................................

/// @ingroup SoloAnyHandle
template< typename T >
inline any_handle
make_any_handle_mutable( std::shared_ptr<T> const &a_shared_pointer_to_copy )
{
    static_assert(!std::is_reference<T>::value, "T should not be a reference type");
    static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value, "T should not be cv-qualified");
    return anys::details::any_handle_builder<T>( a_shared_pointer_to_copy, mutability::true_ );
}

/// @ingroup SoloAnyHandle
inline any_handle
make_any_handle_mutable( std::shared_ptr<void> const &a_type_erased_shared_pointer_to_copy )
{
    return anys::details::any_handle_builder<void>( a_type_erased_shared_pointer_to_copy, mutability::true_ );
}

/// @ingroup SoloAnyHandle
inline any_handle
make_any_handle_mutable( std::shared_ptr<void> &&a_type_erased_shared_pointer_to_move )
{
    return anys::details::any_handle_builder<void>( std::move(a_type_erased_shared_pointer_to_move), mutability::true_ );
}

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLO
////////////////////////////////////////////////////////////////////////////////
