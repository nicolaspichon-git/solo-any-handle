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

/// @ingroup SoloAnyHandleDetails
/// @brief Return a non-mutable reference to the static @em empty @c any_handle_info_wrapper object.
/// @post Return an empty type wrapper.
inline std::experimental::observer_ptr<any_type_info const>
empty_any_type_info_instance_ptr() noexcept
{
    static auto const sti = any_type_info{};
    return std::experimental::make_observer(&sti);
}

////////////////////////////////////////////////////////////////////////////////
}}}}// EONS SOLO::OBS::ANYS::DETAILS
////////////////////////////////////////////////////////////////////////////////
