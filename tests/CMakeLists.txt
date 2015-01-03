################################################################################
# The MIT License (MIT)
#
# Copyright (c) 2014 Abi George Ullattil (Vite Falcon)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
################################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
CMAKE_POLICY(SET CMP0003 NEW)

################################################################################
# Set up the basic build environment
################################################################################
# Just debug / release since that's all that's all we need
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

IF (MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:precise /vmg /Zm1000" CACHE STRING "" FORCE)
    # Enable intrinsics on MSVC in debug mode
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Oi /vmg /Zm1000" CACHE STRING "" FORCE)
ENDIF ()

SET(VITELIBTESTS_PROJECT_NAME "ViteLibTests")

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

INCLUDE(vite_lib_test_dependencies)
INCLUDE(vite_lib_test_files)

ADD_EXECUTABLE(${VITELIBTESTS_PROJECT_NAME} ${VITELIB_TEST_HEADER_FILES} ${VITELIB_TEST_SOURCE_FILES} ${VITELIB_TEST_CMAKE_FILES})
ADD_DEPENDENCIES(${VITELIBTESTS_PROJECT_NAME} ${VITELIB_PROJECT_NAME})
TARGET_LINK_LIBRARIES(${VITELIBTESTS_PROJECT_NAME} ${VITELIBTESTS_LIBRARIES})
SET_TARGET_PROPERTIES(${VITELIBTESTS_PROJECT_NAME} PROPERTIES
    COTIRE_CXX_PREFIX_HEADER_INIT "vite_lib_tests.h"
    COTIRE_UNITY_LINK_LIBRARIES_INIT "COPY"
    COTIRE_ADD_UNITY_BUILD FALSE
)
cotire(${VITELIBTESTS_PROJECT_NAME})