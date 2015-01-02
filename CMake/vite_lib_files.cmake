FILE(GLOB VITELIB_CONFIG_HEADERS "${VITELIB_SOURCE_DIR}/vite/config/*.h")
FILE(GLOB VITELIB_CONFIG_SOURCES "${VITELIB_SOURCE_DIR}/vite/config/*.cpp")

FILE(GLOB VITELIB_EXCEPTION_HEADERS "${VITELIB_SOURCE_DIR}/vite/exception/*.h")
FILE(GLOB VITELIB_EXCEPTION_SOURCES "${VITELIB_SOURCE_DIR}/vite/exception/*.cpp")

FILE(GLOB VITELIB_STRING_HEADERS "${VITELIB_SOURCE_DIR}/vite/string/*.h")
FILE(GLOB VITELIB_STRING_SOURCES "${VITELIB_SOURCE_DIR}/vite/string/*.cpp")

FILE(GLOB VITELIB_VARIANT_HEADERS "${VITELIB_SOURCE_DIR}/vite/variant/*.h")
FILE(GLOB VITELIB_VARIANT_SOURCES "${VITELIB_SOURCE_DIR}/vite/variant/*.cpp")

FILE(GLOB VITELIB_ROOT_HEADERS "${VITELIB_SOURCE_DIR}/vite/*.hpp")

SET(VITELIB_SRCGROUP_SOURCE Source)
# - Root headers
SOURCE_GROUP(${VITELIB_SRCGROUP_SOURCE} FILES ${VITELIB_ROOT_HEADERS})
# - Config files
SOURCE_GROUP(${VITELIB_SRCGROUP_SOURCE}\\config FILES
	${VITELIB_CONFIG_HEADERS}
	${VITELIB_CONFIG_SOURCES}
)
# - Exception files
SOURCE_GROUP(${VITELIB_SRCGROUP_SOURCE}\\exception FILES
	${VITELIB_EXCEPTION_HEADERS}
	${VITELIB_EXCEPTION_SOURCES}
)
# - String file
SOURCE_GROUP(${VITELIB_SRCGROUP_SOURCE}\\string FILES
	${VITELIB_STRING_HEADERS}
	${VITELIB_STRING_SOURCES}
)
# - Variant files
SOURCE_GROUP(${VITELIB_SRCGROUP_SOURCE}\\variant FILES
	${VITELIB_VARIANT_HEADERS}
	${VITELIB_VARIANT_SOURCES}
)

SET(VITELIB_HEADER_FILES
	${VITELIB_ROOT_HEADERS}
	${VITELIB_CONFIG_HEADERS}
	${VITELIB_EXCEPTION_HEADERS}
	${VITELIB_STRING_HEADERS}
	${VITELIB_VARIANT_HEADERS}
)

SET(VITELIB_SOURCE_FILES
	${VITELIB_CONFIG_SOURCES}
	${VITELIB_EXCEPTION_SOURCES}
	${VITELIB_STRING_SOURCES}
	${VITELIB_VARIANT_SOURCES}
)

SET(VITELIB_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

SET(VITELIB_CMAKE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/CMake/vite_lib_dependencies.cmake
	${CMAKE_CURRENT_SOURCE_DIR}/CMake/vite_lib_files.cmake
)

SET(VITELIB_SRCGROUP_CMAKE CMake)
SOURCE_GROUP(${VITELIB_SRCGROUP_CMAKE} FILES ${VITELIB_CMAKE_FILES})