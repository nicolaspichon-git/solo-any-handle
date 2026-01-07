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

/// @defgroup SoloAnyHandleAdvanced AnyHandle Components Requiring Advanced Traits
/// @ingroup SoloAnyHandle
///
/// @defgroup SoloAnyHandleTesting AnyHandle Testing Helpers
/// @ingroup SoloAnyHandle

/// @todo SOLO_ANY_HANDLE_LIBRARY_DECLSPEC
/// @todo Configuration macros to include inlines in .h ou or .cpp

//..............................................................................

#include <solo/anys/handles/any_handle_core_package.hpp>

// advanced any_handle factories:
#include <solo/anys/handles/make_any_handle_ex.hpp>
#include <solo/anys/handles/make_any_handle_mutable_ex.hpp>

// testing helpers:
#include <solo/anys/handles/testing/printing/any_handle_boost_test_outputters.hpp>

////////////////////////////////////////////////////////////////////////////////
