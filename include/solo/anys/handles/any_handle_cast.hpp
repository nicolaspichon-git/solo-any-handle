//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/any_handle.hpp>
#include <type_traits>
#include <stdexcept>
#include <cstdint>

////////////////////////////////////////////////////////////////////////////////
namespace solo {
////////////////////////////////////////////////////////////////////////////////

// -- package

namespace anys
{
    namespace exceptions
    {
        /// @ingroup SoloAnyHandle
        /// @brief The exception thrown by @c any_handle_cast functions on a failed casting operation.
        class bad_any_handle_cast;
    }

    namespace errors
    {
        // .... main cast error

        /// @ingroup SoloAnyHandle
        /// @brief Store diagnostic information on @c any_handle casting operation failures.
        /// @details This is the @c error type of the generic @c result type of @c any_handle casting operations.
        /// @see @c any_handle_cast_result<T, IsMutable>.
        /// @see @c any_handle_cast_errc.
        class any_handle_cast_error;

        // .... integral error codes

        /// @ingroup SoloAnyHandle
        /// @brief The reason why a @c any_handle casting operation could failed.
        /// @see @c any_handle_cast_error.
        enum class any_handle_cast_errc: std::int8_t;

        // .... error diagnosis helpers

        /// @ingroup SoloAnyHandle
        /// @brief Check if the given casting error is due to an empty source.
        constexpr bool is_empty_source_error(any_handle_cast_error const &a_error);

        /// @ingroup SoloAnyHandle
        /// @brief Check if the given casting error is due to a bad source type.
        constexpr bool is_bad_source_type_error(any_handle_cast_error const &a_error);

        /// @ingroup SoloAnyHandle
        /// @brief Check if the given casting error is due to a bad source mutability.
        constexpr bool is_bad_source_mutability_error(any_handle_cast_error const &a_error);
    }

    namespace outcomes
    {
        /// @ingroup SoloAnyHandle
        /// @brief The result of the non-throwing @c solo::any_handle_cast function.
        /// @details May contains a shared pointer of type @c T as value, or an error object
        /// of type @c solo::anys::errors::any_handle_cast_error if casting operation failed.
        template < typename T, solo::mutability IsMutable >
        class any_handle_cast_result;
    }
}

// -- package

/// @ingroup SoloAnyHandle
/// @brief The result type of the operation of casting a @em non-mutable @c any_handle handle.
template < typename T >
using any_handle_cast_result_type = anys::outcomes::any_handle_cast_result<T const, solo::mutability::false_>;

/// @ingroup SoloAnyHandle
/// @brief Cast the given @c any_handle to a typed shared pointer pointing to the @em non-mutable handled object.
/// @param a_handle The type-erased handle to cast.
/// @pre   @c T is the type stored in the given @c a_handle.
/// @post  <c>( result.has_value() && result.assume_value() == a_handle.pointer() ) || ( result.has_error() )</c>
/// @note  Ignore the mutability flag of the given @c a_handle since
/// casting to <c>T const</c> or <c>T</c> returns the same @c shared_ptr<T const> object:
///
/// @code
///
///     auto result1 = any_handle_cast<T const>(ah);
///     auto result2 = any_handle_cast<T>(ah);
///     assert(result1 == result2);
///     assert(std::is_same<decltype(result1), std::shared_ptr<T const>>::value);
///     assert(std::is_same<decltype(result2), std::shared_ptr<T const>>::value);
///
/// @endcode
///
/// This is due to the fact that @c typeid operator ignores cv-qualifiers (@c const, @c volatile).
///
template < typename T >
any_handle_cast_result_type<T> any_handle_cast( solo::any_handle const & ) noexcept;

// -- package

/// @ingroup SoloAnyHandle
/// @brief The result type of the operation of casting a @em mutable @c any_handle handle.
template < typename T >
using any_handle_mutable_cast_result_type = anys::outcomes::any_handle_cast_result<T, solo::mutability::true_>;

/// @ingroup SoloAnyHandle
/// @brief Cast the given @c any_handle to a typed shared pointer pointing to the @em mutable handled object.
/// @param a_handle The type-erased handle to cast.
/// @pre   @c T is the type stored in @c a_handle.
/// @pre   @c a_handle is @em mutable (see @c any_handle).
/// @post  <c>( result.has_value() && result.assume_value() == a_handle.pointer() == a_handle.mutable_pointer() ) || ( result.has_arror() )</c>
/// @note  Casting to <c>T const</c> returns a @c std::shared_ptr<T const> object although the mutability flag is set :
///
/// @code
///
///     auto result1 = any_handle_mutable_cast<T const>(ah);
///     auto result2 = any_handle_cast<T>(ah);
///     assert(result1 == result2);
///     assert(typeid(result1) == typeid(result2));
///     assert(std::is_same<decltype(result1), std::shared_ptr<T const>::value);
///
/// @endcode
///
/// @note The given @c any_handle is passed as a const reference because,
/// whereas the handled object is mutable, the handle itself is not modified
/// by the casting. This is how _handles_ should work.
///
template< typename T >
any_handle_mutable_cast_result_type<T> any_handle_mutable_cast( solo::any_handle const & ) noexcept;

// -- package

/// @ingroup SoloAnyHandle
/// @brief Cast the given @c any_handle to a typed shared pointer pointing to the @em non-mutable handled object.
/// @param a_handle The type-erased handle to cast.
/// @pre   @c T is the type stored in @c a_handle.
/// @post  <c>result == a_handle.pointer()</c>
/// @throw Throw a @c solo::anys::exceptions::bad_any_handle_cast exception if @c T is not the type stored in the given @c a_handle.
/// @note  Ignore the mutability flag of the given @c a_handle.
/// @note  Casting to <c>T const</c> or <c>T</c> returns the same @c shared_ptr<T const> object:
///
/// @code
///
///     auto result1 = any_handle_cast_or_throw<T const>(ah);
///     auto result2 = any_handle_cast_or_throw<T>(ah);
///     assert(result1 == result2);
///     assert(std::is_same<decltype(result1), std::shared_ptr<T const>>::value);
///     assert(std::is_same<decltype(result2), std::shared_ptr<T const>>::value);
///
/// @endcode
///
/// This is due to the fact that @c typeid operator ignores cv-qualifiers (@c const, @c volatile).
///
template< typename T >
std::shared_ptr<T const> any_handle_cast_or_throw( any_handle const & );

// -- package

/// @ingroup SoloAnyHandle
/// @brief Cast the given @c any_handle to a typed shared pointer pointing to the @em mutable handled object.
/// @param a_handle The type-erased handle to cast.
/// @pre   @c T is the type stored in @c a_handle.
/// @pre   @c a_handle is @em mutable (see @c any_handle).
/// @post  <c>result == a_handle.pointer() == a_handle.mutable_pointer()</c>
/// @throw Throw a @c bad_any_handle_cast exception if @c T is not the type stored in @c a_handle.
/// @throw Throw a @c bad_any_handle_cast exception if @c a_handle is not @em mutable (see @c any_handle).
/// @note  Casting to <c>T const</c> returns a @c std::shared_ptr<T const> object although the mutability flag is set :
///
/// @code
///
///     auto result1 = any_handle_mutable_cast<T const>(ah);
///     auto result2 = any_handle_cast<T>(ah);
///     assert(result1 == result2);
///     assert(typeid(result1) == typeid(result2));
///     assert(std::is_same<decltype(result1), std::shared_ptr<T const>::value);
///
/// @endcode
///
/// @note The given @c any_handle is passed as a const reference because,
/// whereas the handled object is mutable, the handle itself is not modified
/// by the casting. This is how _handles_ should work.
///
template< typename T >
std::shared_ptr<T> any_handle_mutable_cast_or_throw( any_handle const &a_handle );

//..............................................................................

// -- definitions

namespace anys
{
    namespace exceptions
    {
        /// @ingroup SoloAnyHandle
        class bad_any_handle_cast
            : public std::runtime_error
        {
        public:

            struct cast_info
            {
                std::type_index type;
                bool mutability;
            };

            /// @brief Explicit member-based constructor.
            /// @param a_failing_handle The @c any_handle object that falied to cast.
            /// @param a_expected_type The type index of the excepted type (the casting target type).
            /// @param a_expected_mutability The excepted mutability type (the casting target mutability).
            /// @see <c>any_handle_cast_or_throw</c>, <c>any_handle_mutable_cast_or_throw</c>.
            ///
            /// Example:
            ///
            ///	@code
            ///     throw bad_any_handle_cast
            ///     {
            ///         the_given_any_handle, typeid(TheGivenTypeToCastTo), the_mutability_casting_operation
            ///     };
            ///	@endcode
            ///
            bad_any_handle_cast
                (
                    any_handle      const &a_failing_handle,
                    std::type_index const &a_expected_type,
                    mutability             a_expected_mutability
                    )
                : std::runtime_error("bad any handle cast")
                , m_actual { cast_info{ a_failing_handle.type(), a_failing_handle.is_mutable()} }
                , m_expected{ cast_info{ a_expected_type, mutability_as_boolean(a_expected_mutability)} }
            {}

            /// @brief The actual type information (the type the failing @c any_handle object has).
            constexpr cast_info const &actual() const noexcept
            {
                return m_actual;
            };

            /// @brief The expected type (what the caller provided).
            constexpr cast_info const &expected() const noexcept
            {
                return m_expected;
            }

        private:

            cast_info m_actual;
            cast_info m_expected;
        };

    }// EONS EXCEPTIONS


    namespace errors
    {
        /// @ingroup SoloAnyHandle
        enum class any_handle_cast_errc: std::int8_t
        {
            undefined = 0,
            empty_source,
            bad_source_type,
            bad_source_mutability
        };

        /// @ingroup SoloAnyHandle
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

    }//EONS ERRORS

    namespace outcomes
    {
        /// @ingroup SoloAnyHandle
        template < typename T, solo::mutability IsMutable >
        class any_handle_cast_result
        {
        public:

            using value_type = std::shared_ptr<T>;

            static_assert(std::is_nothrow_default_constructible<value_type>::value, "");
            static_assert(std::is_nothrow_move_constructible<value_type>::value, "");
            static_assert(std::is_nothrow_move_assignable<value_type>::value, "");

            using error_type = errors::any_handle_cast_error;

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

    }// EONS OUTCOMES

}// EONS ANYS

// -- definitions

/// @ingroup SoloAnyHandle
template < typename T >
inline any_handle_cast_result_type<T>
any_handle_cast( solo::any_handle const &a_handle ) noexcept
{
    using solo::anys::errors::any_handle_cast_error;

    if ( a_handle.empty() )// nothrow
    {
        return any_handle_cast_error{any_handle_cast_error::code_type::empty_source};// nothrow
    }
    if ( a_handle.type() != typeid(T) )// nothrow
    {
        return any_handle_cast_error{any_handle_cast_error::code_type::bad_source_type};// nothrow
    }
    return std::static_pointer_cast<T const>(a_handle.pointer());// nothrow
}

// -- definitions

/// @ingroup SoloAnyHandle
template< typename T >
inline any_handle_mutable_cast_result_type<T>
any_handle_mutable_cast( solo::any_handle const &a_handle ) noexcept
{
    using solo::anys::errors::any_handle_cast_error;

    if ( a_handle.empty() )// nothrow
    {
        return any_handle_cast_error{any_handle_cast_error::code_type::empty_source};// nothrow
    }
    if ( a_handle.type() != typeid(T) )// nothrow
    {
        return any_handle_cast_error{any_handle_cast_error::code_type::bad_source_type};// nothrow
    }
    if ( not a_handle.is_mutable() )// nothrow
    {
        return any_handle_cast_error{any_handle_cast_error::code_type::bad_source_mutability};// nothrow
    }

    return std::static_pointer_cast<T>(a_handle.mutable_pointer());// nothrow
}

// -- definitions

namespace anys { namespace details {

    /// @ingroup SoloAnyHandleDetail
    /// @brief Throw a @c bad_any_handle_cast exception.
    /// @param a_failing_handle The @c any_handle object that failed to cast.
    ///
    /// Example:
    ///
    ///	@code
    ///		template < typename T > std::shared_ptr<const T> cast(any_handle const &ah)
    ///		{
    ///			if (ah.type() == typeid(T))
    ///			{
    ///				return std::static_pointer_cast<const T>( ah.pointer() );
    ///			}
    ///			throw_any_handle_cast_exception<T>(ah, false);
    ///			unreachable_return(nullptr);
    ///		}
    ///
    ///		template < typename T > std::shared_ptr<T> mutable_cast(any_handle &ah)
    ///		{
    ///			if (ah.type() == typeid(T) && ah.is_mutable())
    ///			{
    ///				return std::static_pointer_cast<T>( ah.mutable_pointer() );
    ///			}
    ///			throw_any_handle_cast_exception<T>(ah, true);
    ///			unreachable_return(nullptr);
    ///		}
    /// @endcode
    ///
    template< typename T, mutability IsCastMutable >
    void throw_any_handle_cast_exception( any_handle const &a_failing_handle )
    {
        throw anys::exceptions::bad_any_handle_cast{ a_failing_handle, typeid(T), IsCastMutable };
    };

}}// EONS ANYS::DETAILS

/// @ingroup SoloAnyHandle
template< typename T >
inline std::shared_ptr<T const>
any_handle_cast_or_throw( any_handle const &a_handle )
{
    auto cr = any_handle_cast<T>(a_handle);
    if (cr.has_error())
    {
        anys::details::throw_any_handle_cast_exception<T const,mutability::false_>(a_handle);
        return nullptr;// unreachable
    }
    return std::move(cr).assume_move_value();
}

// -- definitions

/// @ingroup SoloAnyHandle
template< typename T >
inline std::shared_ptr<T>
any_handle_mutable_cast_or_throw( any_handle const &a_handle )
{
    auto cr = any_handle_mutable_cast<T>(a_handle);
    if (cr.has_error())
    {
        anys::details::throw_any_handle_cast_exception<T const,mutability::true_>(a_handle);
        return nullptr;// unreachable
    }
    return std::move(cr).assume_move_value();
}

//..............................................................................

// -- INLINES

namespace anys
{
    namespace errors
    {
        /// @ingroup SoloAnyHandle
        inline constexpr bool is_empty_source_error(any_handle_cast_error const &a_error)
        {
            return a_error.code() == any_handle_cast_errc::empty_source;
        }

        /// @ingroup SoloAnyHandle
        inline constexpr bool is_bad_source_type_error(any_handle_cast_error const &a_error)
        {
            return a_error.code() == any_handle_cast_errc::bad_source_type;
        }

        /// @ingroup SoloAnyHandle
        inline constexpr bool is_bad_source_mutability_error(any_handle_cast_error const &a_error)
        {
            return a_error.code() == any_handle_cast_errc::bad_source_mutability;
        }

    }// EONS ERRORS

}// EONS ANYS

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLO
////////////////////////////////////////////////////////////////////////////////
