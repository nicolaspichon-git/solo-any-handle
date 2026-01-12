//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

#include <solo/anys/handles/exceptions/bad_any_handle_cast.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace anys { namespace details {
////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
}}}// EONS SOLO::ANYS::DETAILS
////////////////////////////////////////////////////////////////////////////////
// EOF
