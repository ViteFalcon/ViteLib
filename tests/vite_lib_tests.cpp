// stdafx.cpp : source file that includes just the standard includes
// RoVariantTest.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "vite_lib_tests.h"
#include "Dependencies/src/gtest-all.cc"
#if roUSE_GMOCK
#   include "Dependencies/src/gmock-all.cc"
#   include "Dependencies/src/gmock_main.cc"
#else
#   include "Dependencies/src/gtest_main.cc"
#endif

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
