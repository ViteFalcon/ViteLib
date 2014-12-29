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

set(VITELIBTESTS_PROJECT_NAME "ViteLibTests")

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

include(vite_lib_test_dependencies)
include(vite_lib_test_files)

add_executable(${VITELIBTESTS_PROJECT_NAME} ${VITELIB_TEST_HEADER_FILES} ${VITELIB_TEST_SOURCE_FILES})
add_dependencies(${VITELIBTESTS_PROJECT_NAME} ${VITELIB_PROJECT_NAME})
target_link_libraries(${VITELIBTESTS_PROJECT_NAME} ${VITELIBTESTS_LIBRARIES})
set_target_properties(${VITELIBTESTS_PROJECT_NAME} PROPERTIES
    COTIRE_CXX_PREFIX_HEADER_INIT "vite_lib_tests.h"
    COTIRE_UNITY_LINK_LIBRARIES_INIT "COPY"
    COTIRE_ADD_UNITY_BUILD FALSE
)
cotire(${VITELIBTESTS_PROJECT_NAME})