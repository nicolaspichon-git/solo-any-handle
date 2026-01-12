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

#include <solo/anys/handles/pragmas/disables_warnings.hpp>
#include <solo/anys/handles/mutability.hpp>
#include <experimental/memory>
#include <typeindex>
#include <utility>

////////////////////////////////////////////////////////////////////////////////
namespace solo {
////////////////////////////////////////////////////////////////////////////////

// -- package

/// @ingroup SoloAnyHandle
/// @brief Point to enhanced runtime c++ type information.
///
/// Add information to the builtin c++ type information @c std::type_index :
/// - mutability,
/// - emptyness ("no-type" type information).
///
/// Note that we want to keep <c>void</c> and <c>const void</c> as valid types,
/// since @c any_handle should be able to store @c std::shared_ptr<void> and @c std::shared_ptr<const void> pointers.
///
/// Design rationale :
/// - safe building operations are delegated to separate templatized builders.
class any_type_index;

// -- package

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_type_index objects.
///
/// The rationale is to compare builtin c++ type information only,
/// ignoring emtyness and mutablity flag, and acting as if @c any_type_index objects
///  were @c std::type_info objects.
///
/// Users should use @c any_type_index::equals method to perfom exact equality comparison
/// between @c any_type_index objects.
///
bool operator==( any_type_index const &, any_type_index const & ) noexcept;
bool operator!=( any_type_index const &, any_type_index const & ) noexcept;
bool operator<=( any_type_index const &, any_type_index const & ) noexcept;
bool operator< ( any_type_index const &, any_type_index const & ) noexcept;
bool operator>=( any_type_index const &, any_type_index const & ) noexcept;
bool operator> ( any_type_index const &, any_type_index const & ) noexcept;

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_type_index and @c std::type_index objects.
/// @see operator==( any_type_index const &, any_type_index const & )
/// @see operator!=( any_type_index const &, any_type_index const & )
/// @see operator<=( any_type_index const &, any_type_index const & )
/// @see operator< ( any_type_index const &, any_type_index const & )
/// @see operator>=( any_type_index const &, any_type_index const & )
/// @see operator> ( any_type_index const &, any_type_index const & )
bool operator==( any_type_index const &, std::type_index const & ) noexcept;
bool operator!=( any_type_index const &, std::type_index const & ) noexcept;
bool operator<=( any_type_index const &, std::type_index const & ) noexcept;
bool operator< ( any_type_index const &, std::type_index const & ) noexcept;
bool operator>=( any_type_index const &, std::type_index const & ) noexcept;
bool operator> ( any_type_index const &, std::type_index const & ) noexcept;
bool operator==( std::type_index const &, any_type_index const & ) noexcept;
bool operator!=( std::type_index const &, any_type_index const & ) noexcept;
bool operator<=( std::type_index const &, any_type_index const & ) noexcept;
bool operator< ( std::type_index const &, any_type_index const & ) noexcept;
bool operator>=( std::type_index const &, any_type_index const & ) noexcept;
bool operator> ( std::type_index const &, any_type_index const & ) noexcept;


/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_type_index and @c std::type_info objects.
/// @see operator==( any_type_index const &, any_type_index const & )
/// @see operator!=( any_type_index const &, any_type_index const & )
/// @see operator<=( any_type_index const &, any_type_index const & )
/// @see operator< ( any_type_index const &, any_type_index const & )
/// @see operator>=( any_type_index const &, any_type_index const & )
/// @see operator> ( any_type_index const &, any_type_index const & )
bool operator==( any_type_index const &, std::type_info const & ) noexcept;
bool operator!=( any_type_index const &, std::type_info const & ) noexcept;
bool operator<=( any_type_index const &, std::type_info const & ) noexcept;
bool operator< ( any_type_index const &, std::type_info const & ) noexcept;
bool operator>=( any_type_index const &, std::type_info const & ) noexcept;
bool operator> ( any_type_index const &, std::type_info const & ) noexcept;
bool operator==( std::type_info const &, any_type_index const & ) noexcept;
bool operator!=( std::type_info const &, any_type_index const & ) noexcept;
bool operator<=( std::type_info const &, any_type_index const & ) noexcept;
bool operator< ( std::type_info const &, any_type_index const & ) noexcept;
bool operator>=( std::type_info const &, any_type_index const & ) noexcept;
bool operator> ( std::type_info const &, any_type_index const & ) noexcept;

//..............................................................................
//..............................................................................

// -- definitions

namespace anys { namespace details {

    /// @ingroup SoloAnyHandleDetails
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
}}

/// @ingroup SoloAnyHandle
class any_type_index
{
public:

    // constructors:

    /// @brief Build an empty @c any_type_index type information.
    /// @post Store a pointer to a static singleton instance of type @c any_type_info .
    any_type_index() noexcept;

    // swapping operation:

    /// @brief Swap @c this with @c another.
    void swap(any_type_index &another) noexcept;

    // copy-move operations:

    /// @brief Default copy constructor.
    constexpr any_type_index(const any_type_index &) noexcept = default;

    /// @brief Default assign-by-copy operator.
    any_type_index &operator=(const any_type_index &) noexcept = default;

    /// @brief Default move constructor.
    /// @post *new this == old another.
    /// @note The moved object is left unchanged (as @c any_type_index doesnt have any ownship).
    constexpr any_type_index(any_type_index &&another) noexcept = default;

    /// @brief Default assign-by-move operator.
    /// @post *new this == old another.
    /// @note The moved object is left unchanged (as @c any_type_index doesnt have any ownship).
    any_type_index &operator=(any_type_index &&another) noexcept = default;

    // properties:

    /// @brief Return the builtin c++ type information.
    /// @note The underlying type could be @c void or <c>const void</c>
    /// whereas the type information is not considered as empty;
    /// Consequently, do not compare the external type index to @c typeid(void)
    /// if you want to check the emptyness of the type information.
    /// Instead use @c is_type_empty.
    constexpr const std::type_index &external_type_index() const noexcept;

    /// @brief Return true if the underlying type is mutable.
    constexpr bool is_type_mutable() const noexcept;

    /// @brief Return true if the type information is empty.
    constexpr bool is_type_empty() const noexcept;

    /// @brief Return true if all type's properties are equal (including mutability and emptiness).
    ///
    ///	The comparison operators compare builtin c++ type information only (acting like if @c any_type_index were @c std::type_index).
    bool equals(const any_type_index &another) const noexcept;

protected:

    // explicit type info-based constructor:

    /// @brief The type of the internal pointer to the @c any_type_info singleton instance.
    using any_type_info_pointer_type = std::experimental::observer_ptr<const anys::details::any_type_info>;

    /// @brief Build a @c any_type_index type information from a static @c any_type_info singleton instance.
    /// @param a_type_info_instance_ptr A static singleton instance of type @c any_type_info .
    /// @post Store a pointer to the given static singleton instance of type @c any_type_info.
    /// @note Building a non-empty @c any_type_index object is delegated to templatized factories.
    /// Templatized factories must be aware that the given @c any_type_info object is a static singleton
    /// that has to survive over any @c any_type_index object.
    constexpr explicit any_type_index( any_type_info_pointer_type a_type_info_instance_ptr ) noexcept;

private:

    any_type_info_pointer_type m_ti_ptr;
};

//..............................................................................

static_assert(sizeof(any_type_index) == sizeof(void*), "");

//..............................................................................
//..............................................................................

// INLINES

namespace anys { namespace details {

    /// @ingroup SoloAnyHandleDetails
    /// @brief Return a non-mutable reference to the static @em empty @c any_handle_info_wrapper object.
    /// @post Return an empty type wrapper.
    inline std::experimental::observer_ptr<any_type_info const>
    empty_any_type_info_instance_ptr() noexcept
    {
        static const auto sti = any_type_info{};
        return std::experimental::make_observer(&sti);
    }

}}// EONS SOLO::ANYS::DETAILS

inline
any_type_index::any_type_index() noexcept
    : any_type_index{ anys::details::empty_any_type_info_instance_ptr() }
{}

inline void
any_type_index::swap(any_type_index &another) noexcept
{
    using std::swap;
    swap(m_ti_ptr,another.m_ti_ptr);
}

inline constexpr const std::type_index &
any_type_index::external_type_index() const noexcept
{
    return m_ti_ptr->m_external_type_index;
}

inline constexpr bool
any_type_index::is_type_mutable() const noexcept
{
    return m_ti_ptr->m_mutable_flag;
}

inline constexpr bool
any_type_index::is_type_empty() const noexcept
{
    return not m_ti_ptr->m_nonempty_flag;
}

inline bool
any_type_index::equals(const any_type_index &another) const noexcept
{
    return m_ti_ptr->m_external_type_index == another.m_ti_ptr->m_external_type_index
            && m_ti_ptr->m_nonempty_flag == another.m_ti_ptr->m_nonempty_flag
            && m_ti_ptr->m_mutable_flag == another.m_ti_ptr->m_mutable_flag;
}

inline constexpr
any_type_index::any_type_index( any_type_index::any_type_info_pointer_type a_type_info_instance_ptr ) noexcept
    : m_ti_ptr{a_type_info_instance_ptr}
{}

//..............................................................................
//..............................................................................

// -- definitions

namespace
{
    inline bool operator==( const std::type_info &a_x, const std::type_index &a_y ) noexcept
    {
        return a_y == a_x;
    }

    inline bool operator!=( const std::type_info &a_x, const std::type_index &a_y ) noexcept
    {
        return a_y != a_x;
    }

    inline bool operator<=( const std::type_info &a_x, const std::type_index &a_y ) noexcept
    {
        return a_y <= a_x;
    }

    inline bool operator< ( const std::type_info &a_x, const std::type_index &a_y ) noexcept
    {
        return a_y <  a_x;
    }

    inline bool operator>=( const std::type_info &a_x, const std::type_index &a_y ) noexcept
    {
        return a_y >= a_x;
    }

    inline bool operator> ( const std::type_info &a_x, const std::type_index &a_y ) noexcept
    {
        return a_y >  a_x;
    }
}

#define SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( op ) \
inline bool operator op ( const any_type_index &a_x, const any_type_index &a_y ) noexcept \
{ \
    return a_x.external_type_index() op a_y.external_type_index(); \
} \
inline bool operator op ( const any_type_index &a_x, const std::type_index &a_y ) noexcept \
{ \
    return a_x.external_type_index() op a_y; \
} \
inline bool operator op ( const std::type_index &a_x, const any_type_index &a_y ) noexcept \
{ \
    return a_x op a_y.external_type_index(); \
} \
inline bool operator op ( const any_type_index &a_x, const std::type_info &a_y ) noexcept \
{ \
    return a_x.external_type_index() op a_y; \
} \
inline bool operator op ( const std::type_info &a_x, const any_type_index &a_y ) noexcept \
{ \
    return a_x op a_y.external_type_index(); \
}

SOLO_DISABLE_WARNING_PUSH
SOLO_DISABLE_WARNING_UNREFERENCED_FUNCTION

SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( == )
SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( != )
SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( < )
SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( <= )
SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( > )
SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR( >= )

SOLO_DISABLE_WARNING_POP

#undef SOLO_DEFINE_ANY_TYPE_INDEX_COMPARISON_OPERATOR

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLO
////////////////////////////////////////////////////////////////////////////////
