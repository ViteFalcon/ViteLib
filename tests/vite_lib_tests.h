// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdio.h>
#include <tchar.h>

#define roUSE_GMOCK 0

#include <gtest/gtest.h>
#if roUSE_GMOCK
#   include <gmock/gmock.h>
#endif

// TODO: reference additional headers your program requires here
