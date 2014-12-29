#-------------------------------------------------------------------------------
# Find Boost
# Prefer static linking in all cases
#-------------------------------------------------------------------------------
if (WIN32 OR APPLE)
    set(Boost_USE_STATIC_LIBS ON)
else ()
    # FIXME: Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
    set(Boost_USE_STATIC_LIBS ON)
endif ()
if (APPLE)
    set(Boost_COMPILER "-xgcc42")
endif()

# Find Boost
find_package(Boost)

if (NOT Boost_FOUND)
    # Try again with the other type of libs
    if(Boost_USE_STATIC_LIBS)
        set(Boost_USE_STATIC_LIBS)
    else()
        set(Boost_USE_STATIC_LIBS ON)
    endif()
    find_package(Boost)
endif()

find_package(Boost REQUIRED)

if (Boost_FOUND)
	list(APPEND VITELIB_INCLUDES ${Boost_INCLUDE_DIRS})
    message("Boost libraries are in ${Boost_LIBRARY_DIRS}")
    if (Boost_USE_STATIC_LIBS)
        message("-- Using static libs")
    else()
        message("-- Using shared libs")
    endif()
    link_directories(${Boost_LIBRARY_DIRS})
    if (NOT WIN32)
        list(APPEND ROKLEGEND_LIBS "libpthread.so")
        list(APPEND ROKLEGEND_LIBS "libdl.so")
        list(APPEND ROKLEGEND_LIBS "libboost_system.a")
        list(APPEND ROKLEGEND_LIBS "libboost_thread.a")
        list(APPEND ROKLEGEND_LIBS "libboost_date_time.a")
        list(APPEND ROKLEGEND_LIBS "libboost_filesystem.a")
        list(APPEND ROKLEGEND_LIBS "libboost_regex.a")
        list(APPEND ROKLEGEND_LIBS "libboost_program_options.a")
    endif()
endif()