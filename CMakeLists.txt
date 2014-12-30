cmake_minimum_required(VERSION 2.8)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)

################################################################################
# Set up the basic build environment
################################################################################
# Just debug / release since that's all that's all we need
set (CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:precise /vmg /Zm1000" CACHE STRING "" FORCE)
    # Enable intrinsics on MSVC in debug mode
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Oi /vmg /Zm1000" CACHE STRING "" FORCE)
endif ()

set(VITELIB_PROJECT_NAME "ViteLib")

project(${VITELIB_PROJECT_NAME})

set(VITELIB_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(VITELIB_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(VITELIB_LIBRARIES debug ${VITELIB_LIB_DIR}/Debug/${VITELIB_PROJECT_NAME}.lib optimized ${VITELIB_LIB_DIR}/Release/${VITELIB_PROJECT_NAME}.lib)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

include(cotire)
include(vite_lib_dependencies)
include(vite_lib_files)

include_directories(
	${VITELIB_INCLUDES}
)

add_library(${VITELIB_PROJECT_NAME} STATIC ${VITELIB_HEADER_FILES} ${VITELIB_SOURCE_FILES})

add_subdirectory(tests)