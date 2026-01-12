//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

// already included : #include <solo/anys/handles/pragmas/disables_warnings.hpp>
#include <solo/anys/handles/any_type_index.hpp>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
namespace solo {
////////////////////////////////////////////////////////////////////////////////

// -- package

/// @ingroup SoloAnyHandle
/// @brief Wrap a type-erased handle of type @c std::shared_ptr<void>.
///
/// Design rationale:
/// - safe building and casting operations are delegated to separate templatized builder/casters.
class any_handle;

// -- package

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_handle objects.
///
/// The rationale is to compare pointers only,
/// ignoring type information, and acting as if @c any_handle objects
/// were raw pointers (as @c std::shared_ptr<T> do).
///
/// Users should use @c any_handle::equals method to perfom exact equality comparison
/// between @c any_handle objects.
///
inline bool operator==( any_handle const &, any_handle const & ) noexcept;
inline bool operator!=( any_handle const &, any_handle const & ) noexcept;
inline bool operator<=( any_handle const &, any_handle const & ) noexcept;
inline bool operator< ( any_handle const &, any_handle const & ) noexcept;
inline bool operator>=( any_handle const &, any_handle const & ) noexcept;
inline bool operator> ( any_handle const &, any_handle const & ) noexcept;

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_handle and @c std::shared_ptr<T> objects.
/// @see operator==( any_handle const &, any_handle const & )
/// @see operator!=( any_handle const &, any_handle const & )
/// @see operator<=( any_handle const &, any_handle const & )
/// @see operator< ( any_handle const &, any_handle const & )
/// @see operator>=( any_handle const &, any_handle const & )
/// @see operator> ( any_handle const &, any_handle const & )
template< typename T > bool operator==( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator!=( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator<=( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator< ( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator>=( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator> ( any_handle const &, std::shared_ptr<T> const & ) noexcept;
template< typename T > bool operator==( std::shared_ptr<T> const &, any_handle const & ) noexcept;
template< typename T > bool operator!=( std::shared_ptr<T> const &, any_handle const & ) noexcept;
template< typename T > bool operator<=( std::shared_ptr<T> const &, any_handle const & ) noexcept;
template< typename T > bool operator< ( std::shared_ptr<T> const &, any_handle const & ) noexcept;
template< typename T > bool operator>=( std::shared_ptr<T> const &, any_handle const & ) noexcept;
template< typename T > bool operator> ( std::shared_ptr<T> const &, any_handle const & ) noexcept;

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_handle object and raw pointer.
/// @see operator==( any_handle const &, any_handle const & )
/// @see operator!=( any_handle const &, any_handle const & )
/// @see operator<=( any_handle const &, any_handle const & )
/// @see operator< ( any_handle const &, any_handle const & )
/// @see operator>=( any_handle const &, any_handle const & )
/// @see operator> ( any_handle const &, any_handle const & )
inline bool operator==( any_handle const &, void const * ) noexcept;
inline bool operator!=( any_handle const &, void const * ) noexcept;
inline bool operator<=( any_handle const &, void const * ) noexcept;
inline bool operator< ( any_handle const &, void const * ) noexcept;
inline bool operator>=( any_handle const &, void const * ) noexcept;
inline bool operator> ( any_handle const &, void const * ) noexcept;
inline bool operator==( void const *, any_handle const & ) noexcept;
inline bool operator!=( void const *, any_handle const & ) noexcept;
inline bool operator<=( void const *, any_handle const & ) noexcept;
inline bool operator< ( void const *, any_handle const & ) noexcept;
inline bool operator>=( void const *, any_handle const & ) noexcept;
inline bool operator> ( void const *, any_handle const & ) noexcept;

/// @ingroup SoloAnyHandle
/// @brief Comparison operators between @c any_handle object and @c nullptr.
/// @see operator==( any_handle const &, any_handle const & )
/// @see operator!=( any_handle const &, any_handle const & )
/// @see operator<=( any_handle const &, any_handle const & )
/// @see operator< ( any_handle const &, any_handle const & )
/// @see operator>=( any_handle const &, any_handle const & )
/// @see operator> ( any_handle const &, any_handle const & )
inline bool operator==( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator!=( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator<=( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator< ( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator>=( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator> ( any_handle const &, std::nullptr_t ) noexcept;
inline bool operator==( std::nullptr_t, any_handle const & ) noexcept;
inline bool operator!=( std::nullptr_t, any_handle const & ) noexcept;
inline bool operator>=( std::nullptr_t, any_handle const & ) noexcept;
inline bool operator> ( std::nullptr_t, any_handle const & ) noexcept;
inline bool operator<=( std::nullptr_t, any_handle const & ) noexcept;
inline bool operator< ( std::nullptr_t, any_handle const & ) noexcept;

//..............................................................................
//..............................................................................

// -- definition:

/// @ingroup SoloAnyHandle
class any_handle
{
public:

    // constructors:

    /// @brief Build an empty @c any_handle object.
    /// @post <c>empty()</c> return true.
    ///
    /// An empty @c any_handle object doesn't handle any object.
    /// It stores a non-typed null pointer and an empty type information.
    any_handle() noexcept = default;

    // swapping operation:

    /// @brief Swap this handle with @c another handle.
    void swap(any_handle &another) noexcept;

    // copy-move operations:

    /// @brief Default copy-constructor.
    any_handle(any_handle const &) noexcept = default;

    /// @brief Default copy-assign operator.
    any_handle &operator=(any_handle const &) noexcept = default;

    /// @brief Default move-constructor.
    /// @post *new this == old another.
    /// @post new another.type() == old another.type().
    /// @post new another.has_value() == false.
    /// @note The moved object's type index object is left unchanged (as @c any_handle doesnt have any ownship on the type index object).
    any_handle(any_handle &&another) noexcept = default;

    /// @brief Default move-assign operator.
    /// @post *new this == old another && new another.type() == old another.type() && new another.pointer() == nullptr.
    any_handle &operator=(any_handle &&another) noexcept = default;

    // diagnosis:

    /// @brief Return true if this handle is empty.
    ///
    /// An @c any_handle object is said @em empty as soon as the handled object's type information is empty. 
    /// An empty @c any_handle object doesn't handle any object and stores a non-typed null pointer.
    /// @note An non-empty @c any_handle object may store a null but typed pointer.
    constexpr bool empty() const noexcept;

    /// @brief Return true if an object is handled.
    /// @post True if and only if : !empty() && pointer() != nullptr.
    /// @note Could be false even if the @c any_handle object is not empty.
    /// @note Always @c false if this handle is empty.
    constexpr bool has_value() const noexcept;

    /// @brief Return the use count of the handled object.
    ///
    /// @note <c>long integer</c> is the standard type of use count returned by @c std::shared_ptr::use_count .
    long use_count() const noexcept;

    /// @brief Return true if the handled object is mutable.
    ///
    ///	The handled object is said @em mutable if it is castable to @c std::shared_ptr<T>
    /// where @c T is the plain handled object's type.
    ///
    /// @note Return @c false if this handle is empty.
    constexpr bool is_mutable() const noexcept;

    /// @brief Return true if all handle's properties are equal.
    ///
    ///	The comparison operators compare pointers only (acting like if @c any_handle were a raw pointer).
    ///
    bool equals( any_handle const &another ) const noexcept;

    // properties:

    /// @brief The type information type.
    using type_index_type = std::type_index;

    /// @brief Get the handled object's type information.
    /// @note Could return @c typeid(void) even if this handle is not empty.
    constexpr type_index_type const &type() const noexcept;

    /// @brief The type-erased shared non-mutable pointer type.
    using pointer_type = std::shared_ptr<const void>;

    /// @brief Get a type-erased shared pointer to the non-mutable object.
    /// @return A type-erased shared pointer to the non-mutable handled object.
    ///
	/// @note Return a null pointer if this handle is empty.
    /// @note The pointer may be null even if its type information is not.
    pointer_type pointer() const noexcept;

    /// @brief The type-erased shared mutable pointer type.
    using mutable_pointer_type = std::shared_ptr<void>;

    /// @brief Get a type-erased shared pointer to the mutable object.
    /// @return If the handled object is mutable, a type-erased shared pointer to the mutable handled object.
    /// Otherwise, a null pointer.
    ///
    /// @note Return a null pointer if the handle is empty.
    /// @note The pointer may be null even if its type information is not.
    mutable_pointer_type mutable_pointer() const noexcept;

protected:

    // explicit constructor:

    /// @brief We need an internal type index that can handle the mutabble flag.
    using internal_type_index_type = any_type_index;

    /// @brief Explicit member-based constructor (copying the given shared pointer).
    /// @param a_ti The enhanced type information to store.
    /// @param a_sp The type-erased shared pointer to store.
    /// @pre The caller is responsible for the consistency between 
	/// the handled object's type information and the handled object's type-erased pointer.
    /// @post ( type() == a_ti.external_type() )
    /// @post ( empty() ) == a_ti.is_type_empty() )
    /// @post ( mutable() ) == a_ti.is_type_mutable() )
    /// @post ( pointer() == mutable_pointer() )
    /// @post ( empty() ) ==> ( type() == typeid(void) && pointer() == nullptr ).
    /// @post ( not(empty()) ) ==> ( pointer() == a_sp ).
    /// @see @c make_any_handle, @c make_any_handle_base, @c make_any_type_index.
    ///
    /// @note The safe template-based construction is delegated to the factory function @c make_any_handle.
    /// The rationale is to remove any templated members from the class @c any_handle.
    /// It allows users to include @c any_handle members in class declaration
    /// without being polluted by templates definitions.
    ///
    explicit any_handle( internal_type_index_type const &a_ti, mutable_pointer_type const &a_sp ) noexcept;

    /// @brief Explicit member-based constructor (moving the given shared pointer).
    /// @param a_ti The enhanced type information to store.
    /// @param a_sp The type-erased shared pointer to store.
    /// @pre The caller is responsible for the consistency between
    /// the handled object's type information and the handled object's type-erased pointer.
    /// @post ( type() == a_ti.external_type() )
    /// @post ( empty() ) == a_ti.is_type_empty() )
    /// @post ( mutable() ) == a_ti.is_type_mutable() )
    /// @post ( pointer() == mutable_pointer() )
    /// @post ( empty() ) ==> ( type() == typeid(void) && pointer() == nullptr ).
    /// @post ( not(empty()) ) ==> ( pointer() == copy of a_sp ).
    /// @see @c make_any_handle, @c make_any_handle_base, @c make_any_type_index.
    /// @see <c>any_handle(internal_type_index_type const &a_ti, mutable_pointer_type const &)</c>.
    explicit any_handle( internal_type_index_type const &a_ti, mutable_pointer_type &&a_sp ) noexcept;

private:

    // data:
	
    internal_type_index_type m_ti;
    mutable_pointer_type m_pointer;
};

//..............................................................................

static_assert(sizeof(any_handle) == sizeof(std::shared_ptr<void>) + sizeof(void*), "");

//..............................................................................
//..............................................................................

// INLINES

inline
any_handle::any_handle( any_handle::internal_type_index_type const &a_ti, any_handle::mutable_pointer_type const &a_sp ) noexcept
    : m_ti{ a_ti }
    , m_pointer{ a_ti.is_type_empty() ? nullptr : a_sp }// copy the given shared pointer
{}

inline
any_handle::any_handle( any_handle::internal_type_index_type const &a_ti, any_handle::mutable_pointer_type &&a_sp ) noexcept
  : m_ti{ a_ti }
  , m_pointer{ a_ti.is_type_empty() ? nullptr : std::move(a_sp) }// move the given shared pointer
{}

inline void
any_handle::swap(any_handle &another) noexcept
{
    using std::swap;
    swap(m_ti,another.m_ti);
    swap(m_pointer,another.m_pointer);
}

inline constexpr bool
any_handle::empty() const noexcept
{
    return m_ti.is_type_empty();
}

inline constexpr bool
any_handle::has_value() const noexcept
{
    return !empty() && m_pointer != nullptr;
}

inline long
any_handle::use_count() const noexcept
{
    return m_pointer ? m_pointer.use_count() : 0;
}

inline constexpr bool
any_handle::is_mutable() const noexcept
{
    return m_ti.is_type_mutable();
}

inline bool
any_handle::equals( any_handle const &another ) const noexcept
{
    return m_ti.equals(another.m_ti) && m_pointer == another.m_pointer;
}

inline constexpr any_handle::type_index_type const &
any_handle::type() const noexcept
{
    return m_ti.external_type_index();
}

inline any_handle::pointer_type
any_handle::pointer() const noexcept
{
    return m_pointer;
}

inline any_handle::mutable_pointer_type
any_handle::mutable_pointer() const noexcept
{
    return m_ti.is_type_mutable() ? m_pointer : nullptr;
}

//..............................................................................
//..............................................................................

// -- definitions

#define SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( op ) \
inline bool operator op ( any_handle const &a_x, any_handle const &a_y ) noexcept \
{ \
        return a_x.pointer() op a_y.pointer(); \
} \
    template< typename T > \
    inline bool operator op ( any_handle const &a_x, std::shared_ptr<T> const &a_y ) noexcept \
{ \
        return a_x.pointer() op a_y; \
} \
    template< typename T > \
    inline bool operator op ( std::shared_ptr<T> const &a_x, any_handle const &a_y ) noexcept \
{ \
        return a_x op a_y.pointer(); \
} \
    inline bool operator op ( any_handle const &a_x, void const *a_y ) noexcept \
{ \
        return a_x.pointer().get() op a_y; \
} \
    inline bool operator op ( void const *a_x, any_handle const &a_y ) noexcept \
{ \
        return a_x op a_y.pointer().get(); \
} \
    inline bool operator op ( any_handle const &a_x, std::nullptr_t ) noexcept \
{ \
        return a_x.pointer() op nullptr; \
} \
    inline bool operator op ( std::nullptr_t, any_handle const &a_y ) noexcept \
{ \
        return nullptr op a_y.pointer(); \
}

SOLO_DISABLE_WARNING_PUSH
    SOLO_DISABLE_WARNING_UNREFERENCED_FUNCTION

            SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( == )
    SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( != )
    SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( < )
    SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( <= )
    SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( > )
    SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR( >= )

    SOLO_DISABLE_WARNING_POP

#undef SOLO_DEFINE_ANY_HANDLE_COMPARISON_OPERATOR

////////////////////////////////////////////////////////////////////////////////
}// EONS SOLO
////////////////////////////////////////////////////////////////////////////////
