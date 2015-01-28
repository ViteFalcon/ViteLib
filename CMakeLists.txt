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
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.10)

SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
CMAKE_POLICY(SET CMP0003 NEW)

################################################################################
# Setup the basic build environment
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
ENDIF (MSVC)

SET(VITELIB_PROJECT_NAME "ViteLib")

PROJECT(${VITELIB_PROJECT_NAME})

SET(VITELIB_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
SET(VITELIB_LIB_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
SET(VITELIB_BINARIES_DIR_DBG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
SET(VITELIB_BINARIES_DIR_REL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
SET(VITELIB_LIBRARIES debug ${VITELIB_LIB_DIR}/Debug/${VITELIB_PROJECT_NAME}.lib optimized ${VITELIB_LIB_DIR}/Release/${VITELIB_PROJECT_NAME}.lib)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Packages")

INCLUDE(cotire)
INCLUDE(vite_lib_dependencies)
INCLUDE(vite_lib_files)

INCLUDE_DIRECTORIES(
    ${VITELIB_INCLUDES}
)

ADD_LIBRARY(${VITELIB_PROJECT_NAME} SHARED ${VITELIB_HEADER_FILES} ${VITELIB_SOURCE_FILES} ${VITELIB_CMAKE_FILES})
TARGET_LINK_LIBRARIES(${VITELIB_PROJECT_NAME} ${VITELIB_LIBS})

COPY_FILES_INTO_DIRECTORY_IF_CHANGED(${VITELIB_BINARIES_DBG} ${VITELIB_BINARIES_DIR_DBG} ${VITELIB_PROJECT_NAME})
COPY_FILES_INTO_DIRECTORY_IF_CHANGED(${VITELIB_BINARIES_REL} ${VITELIB_BINARIES_DIR_REL} ${VITELIB_PROJECT_NAME})

ADD_SUBDIRECTORY(tests)