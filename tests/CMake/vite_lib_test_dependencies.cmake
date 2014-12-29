include_directories(
    ${VITELIB_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/include
)
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND VITELIBTESTS_LIBRARIES ${VITELIB_LIBRARIES})