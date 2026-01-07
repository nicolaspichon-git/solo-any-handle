//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

// LAST CHANGES:
//  - 2021/11/20 : delegate the @c any_type_info templatized constructor to @c make_any_type_info.
//  - 2021/11/21 : rename casting method any_handle_xxx_cast to any_handle_xxx_cast_or_throw.
//  - 2021/11/21 : new non-throwing casting methods any_handle_xxx_cast with @c any_handle_cast_result.
//  - 2021/11/22 : handle @c any_type_info singletons by observer pointers.

/// @cond 

#define SOLO_ANY_HANDLE_VERSION_NUMBER_MAJOR	1
#define SOLO_ANY_HANDLE_VERSION_NUMBER_MINOR	0
#define SOLO_ANY_HANDLE_VERSION_NUMBER_PATCH	0

#define SOLO_ANY_HANDLE_VERSION_PRERELEASE_STRING	"alpha-004"

/// @endcond

////////////////////////////////////////////////////////////////////////////////
