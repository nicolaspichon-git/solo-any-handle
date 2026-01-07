//------------------------------------------------------------------------------
//
// Copyright (c) 2021 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------
#pragma once

// source : https://www.fluentcpp.com/2019/08/30/how-to-disable-a-warning-in-cpp

#if defined(_MSC_VER)
#define SOLO_DISABLE_WARNING_PUSH           __pragma(warning( push ))
#define SOLO_DISABLE_WARNING_POP            __pragma(warning( pop ))
#define SOLO_DISABLE_WARNING(warningNumber) __pragma(warning( disable : warningNumber ))

#define SOLO_DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER    SOLO_DISABLE_WARNING(4100)
#define SOLO_DISABLE_WARNING_UNREFERENCED_FUNCTION            SOLO_DISABLE_WARNING(4505)
#define SOLO_DISABLE_WARNING_UNREFERENCED_FUNCTION
#define SOLO_DISABLE_WARNING_IMPLICIT_FALLTHROUGH
// other warnings you want to deactivate...

#elif defined(__GNUC__) || defined(__clang__)
#define SOLO_DO_PRAGMA(X) _Pragma(#X)
#define SOLO_DISABLE_WARNING_PUSH           SOLO_DO_PRAGMA(GCC diagnostic push)
#define SOLO_DISABLE_WARNING_POP            SOLO_DO_PRAGMA(GCC diagnostic pop)
#define SOLO_DISABLE_WARNING(warningName)   SOLO_DO_PRAGMA(GCC diagnostic ignored #warningName)

#define SOLO_DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER    SOLO_DISABLE_WARNING(-Wunused-parameter)
#define SOLO_DISABLE_WARNING_UNREFERENCED_FUNCTION            SOLO_DISABLE_WARNING(-Wunused-function)
#define SOLO_DISABLE_WARNING_UNREFERENCED_VARIABLE            SOLO_DISABLE_WARNING(-Wunused-variable)
#define SOLO_DISABLE_WARNING_IMPLICIT_FALLTHROUGH             SOLO_DISABLE_WARNING(-Wimplicit-fallthrough)
// other warnings you want to deactivate...
#else
#define SOLO_DISABLE_WARNING_PUSH
#define SOLO_DISABLE_WARNING_POP
#define SOLO_DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER
#define SOLO_DISABLE_WARNING_UNREFERENCED_FUNCTION
#define SOLO_DISABLE_WARNING_UNREFERENCED_VARIABLE
#define SOLO_DISABLE_WARNING_IMPLICIT_FALLTHROUGH
// other warnings you want to deactivate...

#endif

////////////////////////////////////////////////////////////////////////////////
