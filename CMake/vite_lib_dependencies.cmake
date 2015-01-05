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

# This sets the following variables
# 1. VITELIB_INCLUDES: A list of directories that are required by ViteLib
# 2. VITELIB_BINARIES_REL: A list of binaries that needs to be copied over to the release binary directory
# 2. VITELIB_BINARIES_DBG: A list of binaries that needs to be copied over to the debug binary directory

IF (WIN32)
    SET(VITE_LIB_BIN_EXT ".dll")
ELSEIF (LINUX)
    SET(VITE_LIB_BIN_EXT ".so")
ELSE ()
    SET(VITE_LIB_BIN_EXT "")
ENDIF ()

#-------------------------------------------------------------------------------
# Find Boost
# Prefer static linking in all cases
#-------------------------------------------------------------------------------
IF (WIN32 OR APPLE)
    SET(Boost_USE_STATIC_LIBS ON)
ELSE ()
    # FIXME: Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
    SET(Boost_USE_STATIC_LIBS ON)
ENDIF ()
IF (APPLE)
    SET(Boost_COMPILER "-xgcc42")
ENDIF ()

# Find Boost
FIND_PACKAGE(Boost)

IF (NOT Boost_FOUND)
    # Try again with the other type of libs
    IF (Boost_USE_STATIC_LIBS)
        SET(Boost_USE_STATIC_LIBS)
    ELSE ()
        SET(Boost_USE_STATIC_LIBS ON)
    ENDIF ()
    FIND_PACKAGE(Boost)
ENDIF ()

FIND_PACKAGE(Boost REQUIRED)

IF (Boost_FOUND)
    LIST(APPEND VITELIB_INCLUDES ${Boost_INCLUDE_DIRS})
    MESSAGE("Boost libraries are in ${Boost_LIBRARY_DIRS}")
    IF (Boost_USE_STATIC_LIBS)
        MESSAGE("-- Using static libs")
    ELSE ()
        MESSAGE("-- Using shared libs")
    ENDIF ()
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    IF (NOT WIN32)
        LIST(APPEND VITELIB_LIBS "libpthread.so")
        LIST(APPEND VITELIB_LIBS "libdl.so")
        LIST(APPEND VITELIB_LIBS "libboost_system.a")
        LIST(APPEND VITELIB_LIBS "libboost_thread.a")
        LIST(APPEND VITELIB_LIBS "libboost_date_time.a")
        LIST(APPEND VITELIB_LIBS "libboost_filesystem.a")
        LIST(APPEND VITELIB_LIBS "libboost_regex.a")
        LIST(APPEND VITELIB_LIBS "libboost_program_options.a")
    ENDIF ()
ENDIF ()

SET(TBB_INSTALL_DIR $ENV{TBB_INSTALL_DIR})
IF (CMAKE_SIZEOF_VOID_P EQUAL 4)
    SET(TBB_ARCHITECTURE ia32)
ELSE ()
    SET(TBB_ARCHITECTURE intel64)
ENDIF ()

FIND_PACKAGE(TBB REQUIRED)

IF (TBB_FOUND)
    LIST(APPEND VITELIB_INCLUDES ${TBB_INCLUDE_DIRS})
    MESSAGE("TBB LIB DIRS: ${TBB_LIBRARY_DIRS}")
    LIST(APPEND VITELIB_LIBS debug ${TBB_LIBRARY_DEBUG} optimized ${TBB_LIBRARY})
    IF (WIN32)
        MESSAGE("Dirs: ${TBB_LIBRARY_DIRS}")
        STRING(REPLACE "/lib/" "/bin/" TBB_BIN_DIR ${TBB_LIBRARY_DIRS})
        
        GET_FILENAME_COMPONENT(TBB_LIBRARY_FILENAME ${TBB_LIBRARY} NAME)
        STRING(REPLACE ".lib" ${VITE_LIB_BIN_EXT} TBB_BINARY_FILENAME ${TBB_LIBRARY_FILENAME})
        
        GET_FILENAME_COMPONENT(TBB_LIBRARY_DEBUG_FILENAME ${TBB_LIBRARY_DEBUG} NAME)
        STRING(REPLACE ".lib" ${VITE_LIB_BIN_EXT} TBB_BINARY_DEBUG_FILENAME ${TBB_LIBRARY_DEBUG_FILENAME})
        
        LIST(APPEND VITELIB_BINARIES_REL ${TBB_BIN_DIR}/${TBB_BINARY_FILENAME})
        LIST(APPEND VITELIB_BINARIES_DBG ${TBB_BIN_DIR}/${TBB_BINARY_DEBUG_FILENAME})
    ENDIF ()
ENDIF ()

###################################################################################################
#                           ADD ALL DEPENDENCIES ABOVE THIS SECTION                               #
###################################################################################################
MACRO(COPY_FILE_IF_CHANGED in_file out_file target)
    IF (${in_file} IS_NEWER_THAN ${out_file})
        MESSAGE("Copying file '${in_file}' to '${out_file}'")
        ADD_CUSTOM_COMMAND (
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            ARGS -E copy ${in_file} ${out_file}
        )
    ENDIF ()
ENDMACRO()

MACRO(COPY_FILE_INTO_DIRECTORY_IF_CHANGED in_file out_dir target)
    GET_FILENAME_COMPONENT(file_name ${in_file} NAME)
    COPY_FILE_IF_CHANGED(${in_file} ${out_dir}/${file_name} ${target})
ENDMACRO()

#Copies all the files from in_file_list into the out_dir. 
# sub-trees are ignored (files are stored in same out_dir)
MACRO(COPY_FILES_INTO_DIRECTORY_IF_CHANGED in_file_list out_dir target)
    FOREACH (in_file ${in_file_list})
        COPY_FILE_INTO_DIRECTORY_IF_CHANGED(${in_file} ${out_dir} ${target})
    ENDFOREACH ()
ENDMACRO()