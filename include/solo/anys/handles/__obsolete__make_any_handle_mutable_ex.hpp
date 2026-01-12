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

#include <solo/anys/handles/make_any_handle.hpp>

#include <stdex/in_place_t.hpp>
#include <stdex/in_place_type_t.hpp>
#include <stdex/observer_ptr.hpp>
#include <boost/hof/is_invocable.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace obsolete {
////////////////////////////////////////////////////////////////////////////////

// -- package

/// @ingroup SoloAnyHandleAdvanced
/// @brief Safely build a mutable @c any_handle object, building @em in-place an
/// object of type @c T.
/// @pre @c T is a plain type (not a reference type, not cv-qualified).
/// @pre @c T is constructible from @c args .
/// @param a_type_constructor_arguments_list A list of arguments from which the
/// object can be constructed.
///
/// Example:
///
/// @code
///     // 1. use the global tag object stdex::in_place
///     // 2. make_any_handle_mutable<A>(stdex::in_place, args) will call the A's constructor which accepts arguments 'args': A{args}
///     auto y = make_any_handle<A>(stdex::in_place, args);
///     assert(y.use_count() == 1);
///     assert(y.type() == typeid(A));
///     assert(y.is_mutable() == true);
/// @endcode
///
/// @note If the template type @c T has a @c const qualifier, then the @c const
/// qualifier is removed and the inner shared pointer is of type
/// @c T' = @c std::remove_const_t<T>.
/// @note @c make_any_handle_mutable<T>(stdex::in_place, args) as the same effect
/// than @c make_any_handle_mutable<T>(stdex::in_place_type<T>, args).
template < typename T, typename... Args >
any_handle make_any_handle_mutable( stdex::in_place_t, Args&&... a_type_constructor_arguments_list );

/// @ingroup SoloAnyHandleAdvanced
/// @brief Safely build a mutable @c any_handle object,
/// building @em in-place an object of type @c U @em where @c U* is convertible to @c T*.
/// @pre @c T is a plain type (not a reference type, not cv-qualified).
/// @pre @c U is a plain type (not a reference type, not cv-qualified).
/// @pre @c U is constructible from @c args .
/// @pre @c U* is convertible to @c T*.
/// @param a_type_constructor_arguments_list A list of arguments from which the
/// object can be constructed.
///
/// Example:
///
/// @code
///     // 1. use the global tag object stdex::in_place_type_t<B>
///     // 2. make_any_handle_mutable<A>(stdex::in_place_type<B>, args) will
///     //    a. call the B's constructor which accepts arguments 'args': B{args}
///     //    b. build a shared pointer of type A from the previously built object of type B.
///     auto y = make_any_handle_mutable<A>(stdex::in_place_type<B>, args);
///     assert(y.use_count() == 1);
///     assert(y.type() == typeid(A));
///     assert(y.is_mutable() == true);
/// @endcode
///
/// @note If the template type @c T has a @c const qualifier, then the @c const
/// qualifier is removed and the inner shared pointer is of type
/// @c T' = @c std::remove_const_t<T>.
/// @note Use @c make_any_handle_mutable<T>(stdex::in_place, args) instead of
/// @c make_any_handle_mutable<T>(stdex::in_place_type<T>, args).
template < typename T, typename U, typename... Args >
any_handle make_any_handle_mutable( stdex::in_place_type_t<U>, Args&&... a_type_constructor_arguments_list );

/// @ingroup SoloAnyHandleAdvanced
/// @brief Safely build a mutable @c any_handle object
/// from an @em observer pointer (i.e. a non-owned pointer) to an already-built
/// object of type @c T.
/// @pre @c T is a plain type (not a reference type, not cv-qualified).
/// @param a_non_owned_pointer_to_copy A @c stdex::observer pointer of type @c T.
///
/// Example:
///
/// @code
///     auto x = T{...};
///     {
///         auto y = make_any_handle_mutable(stdex::make_observer(&x));
///         assert(y.use_count() == 1);
///         assert(y.pointer().get() == &x);
///         assert(y.type() == typeid(T));
///         assert(y.is_mutable() == true);
///     }
///     // you can still use x from here because the pointee object hasnt been deleted.
/// @endcode
///
/// @note If the template type @c T has a @c const qualifier, then the @c const qualifier
/// is removed and the inner shared pointer is of type @c T' = @c std::remove_const_t<T>.
/// @note The main point is that the shared pointer built around the object pointed by
/// @c op won't delete the pointee object after the shared count felt to zero.
template < typename T >
any_handle make_any_handle_mutable( stdex::observer_ptr<T> const &a_non_owned_pointer_to_copy );

/// @ingroup SoloAnyHandleAdvanced
/// @brief Safely build a mutable @c any_handle object
/// from a pointer to an already-built object of type @c T and a @em customized finalizer.
/// @pre @c T is a plain type (not a reference type nor cv-qualified).
/// @param a_raw_pointer_to_copy A raw pointer pointing to an object of type @c T.
/// @param a_callable_finalizer A callable object with signature @c void(T*).
///
/// Example:
///
/// @code
///     auto x = A{};
///     {
///         // build a shared pointer of type std::shared_ptr<A> :
///         auto y = make_any_handle_mutable(&x , [](A *p){ std::cout << "delete x" << std::endl; } );
///         assert(y.use_count() == 1);
///         assert(y.mutable_pointer().get() == &x);
///         assert(y.type() == typeid(A));
///         assert(y.is_mutable() == true);
///     }
///
///     // you can still use x from here because the customized finalizer is not destructive.
///
///     struct B : A {};
///     auto z = B{};
///     {
///         // explicitly build a shared pointer of type std::shared_ptr<A> :
///         auto y = make_any_handle<A>(&z , [](A *p){ std::cout << "delete z" << std::endl; } );
///         assert(y.use_count() == 1);
///         assert(y.mutable_pointer().get() == &y);
///         assert(y.type() == typeid(A));
///         assert(y.is_mutable() == true);
///     }
/// @endcode
///
/// @note If the template type @c T has a @c const qualifier, then the @c const qualifier
/// is removed and the inner shared pointer is of type @c T' = @c std::remove_const_t<T>.
template < typename T, typename F >
any_handle make_any_handle_mutable( T *a_raw_pointer_to_copy, F &&a_callable_finalizer );

//..............................................................................
//..............................................................................

// -- definitions

/// @ingroup SoloAnyHandleAdvanced
template < typename T, typename... Args >
inline any_handle
make_any_handle_mutable( stdex::in_place_t, Args&&... a_type_constructor_arguments_list )
{
    static_assert(!std::is_reference<T>::value, "T should not be a reference type");
    static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value, "T should not be cv-qualified");

    // call the first factory :
    return make_any_handle_mutable( std::make_shared<T>(std::forward<Args>(a_type_constructor_arguments_list)...) );
}

/// @ingroup SoloAnyHandleAdvanced
template < typename T, typename U, typename... Args >
inline any_handle
make_any_handle_mutable( stdex::in_place_type_t<U>, Args&&... a_type_constructor_arguments_list )
{
    static_assert(!std::is_reference<T>::value, "T should not be a reference type");
    static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value, "T should not be cv-qualified");
    static_assert(!std::is_reference<U>::value, "U should not be a reference type");
    static_assert(!std::is_const<U>::value && !std::is_volatile<U>::value, "U should not be cv-qualified");

    // call the first factory :
    return make_any_handle_mutable<T>( std::make_shared<U>(std::forward<Args>(a_type_constructor_arguments_list)...) );
}

/// @ingroup SoloAnyHandleAdvanced
template < typename T >
inline any_handle
make_any_handle_mutable( stdex::observer_ptr<T> const &a_non_owned_pointer_to_copy )
{
    static_assert(!std::is_reference<T>::value, "T should not be a reference type");
    static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value, "T should not be cv-qualified");

    // call the first factory :
    return make_any_handle_mutable( std::shared_ptr<T>(a_non_owned_pointer_to_copy.get(), [](T*){} ) );
}

/// @ingroup SoloAnyHandleAdvanced
template < typename T, typename F >
inline any_handle
make_any_handle_mutable( T *a_raw_pointer_to_copy, F &&a_callable_finalizer )
{
    static_assert(!std::is_reference<T>::value, "T should not be a reference type");
    static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value, "T should not be cv-qualified");
    static_assert(boost::hof::is_invocable<F,std::remove_const_t<T>*>::value, "Bad finalizer signature");

    // call the first factory :
    return make_any_handle_mutable( std::shared_ptr<T>{ a_raw_pointer_to_copy, std::forward<F>(a_callable_finalizer) } );
}

////////////////////////////////////////////////////////////////////////////////
}}// EONS SOLO::OBS
////////////////////////////////////////////////////////////////////////////////
