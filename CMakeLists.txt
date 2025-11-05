cmake_minimum_required(VERSION 3.7...3.14)

# These must be set before we reach the 'project' directive so that CMake can use
# them to make toolchain selections during the 'configure' phase.
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(TCLAP VERSION 1.4.0 LANGUAGES CXX)
set("PROJECT_DESCRIPTION" "A header-only templatized C++ command line parser library")
set("PROJECT_HOMEPAGE_URL" "https://sourceforge.net/projects/tclap/")

# Determine if we are a standalone project or a dependency (not the master CMakeLists)
# Using option makes it simple for a consumer to set the value prior to including.
# NOTE: CMake 3.21+ handles this thru 'PROJECT_IS_TOP_LEVEL' or 'TCLAP_IS_TOP_LEVEL')
# See: https://cmake.org/cmake/help/latest/command/project.html#synopsis
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	option(TCLAP_STANDALONE_BUILD "Build TCLAP as a standalone library/package" ON)
else()
	option(TCLAP_STANDALONE_BUILD "BUILD TCLAP as a standalone library/package" OFF)
endif()
message(VERBOSE "TCLAP_STANDALONE_BUILD: ${TCLAP_STANDALONE_BUILD}")

# Identify what we need to build/include.
option(BUILD_EXAMPLES "Build examples" ${TCLAP_STANDALONE_BUILD})
option(BUILD_TESTS "Build TCLAP tests" ${TCLAP_STANDALONE_BUILD})
option(BUILD_UNITTESTS "Build unit tests" ${TCLAP_STANDALONE_BUILD})
option(BUILD_DOC "Build documentation" ${TCLAP_STANDALONE_BUILD})
option(BUILD_PACKAGE "Build package" ${TCLAP_STANDALONE_BUILD})

if(BUILD_TESTS OR BUILD_UNITTESTS)
  enable_testing()
  include(CTest)
endif()

add_library(TCLAP INTERFACE)
target_include_directories(TCLAP INTERFACE
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)
target_compile_definitions(TCLAP INTERFACE -DHAVE_TCLAP_CONFIG_H)

# Generate a config file.
include (cmake/ConfigH.cmake)

install(TARGETS TCLAP EXPORT TCLAP
  INCLUDES
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES "${GENERATED_CONFIG_BUILD_PATH}"
  DESTINATION include/tclap
  COMPONENT lib
)

if(${CMAKE_VERSION} VERSION_GREATER "3.14")
	set(OPTIONAL_ARCH_INDEPENDENT "ARCH_INDEPENDENT")
endif()

message(VERBOSE "TCLAP BUILD_DOC is ${BUILD_DOC}")
if(BUILD_DOC)
	add_subdirectory(docs)
endif()
message(VERBOSE "TCLAP BUILD_EXAMPLES is ${BUILD_EXAMPLES}")
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
message(VERBOSE "TCLAP BUILD_TESTS is ${BUILD_TESTS}")
if(BUILD_TESTS)
	add_subdirectory(tests)
endif()
message(VERBOSE "TCLAP BUILD_UNITTESTS is ${BUILD_UNITTESTS}")
if(BUILD_UNITTESTS)
	add_subdirectory(unittests)
endif()

add_subdirectory(include/tclap)

message(VERBOSE "TCLAP BUILD_PACKAGE is ${BUILD_PACKAGE}")
if(BUILD_PACKAGE)
	include(cmake/Package.cmake)
endif()
