cmake_minimum_required(VERSION 3.7)

project(TCLAP VERSION 1.4.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-DHAVE_TCLAP_CONFIG_H)

enable_testing()
include(CTest)

include(CheckCXXSourceCompiles)
check_cxx_source_compiles("#include <strstream>
int main() { std::istrstream iss; }" TCLAP_HAVE_STRSTREAM)

check_cxx_source_compiles("#include <sstream>
int main() { std::istringstream iss; }" TCLAP_HAVE_SSTREAM)

configure_file(config.h.in tclap/TCLAPConfig.h)

add_library(TCLAP INTERFACE)
target_include_directories(TCLAP INTERFACE include/)
install(TARGETS TCLAP DESTINATION include)
install(FILES ${PROJECT_BINARY_DIR}/tclap/TCLAPConfig.h
  DESTINATION include/tclap
  )

if(DOC_INSTALL_DIR)
else()
  if(WIN32)
    set(DOC_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/doc)
  else()
    set(DOC_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/doc/tclap)
  endif()
endif()

install(DIRECTORY ${PROJECT_BINARY_DIR}/docs/html
  DESTINATION ${DOC_INSTALL_DIR})
install(FILES ${PROJECT_BINARY_DIR}/docs/index.html ${PROJECT_BINARY_DIR}/docs/manual.html
  ${PROJECT_BINARY_DIR}/docs/style.css DESTINATION ${DOC_INSTALL_DIR})

option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_UNITTESTS "Build unit tests" ON)
option(BUILD_DOC "Build documentation" ON)

if(BUILD_DOC)
	add_subdirectory(docs)
endif()
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
add_subdirectory(tests)
if(BUILD_UNITTESTS)
	add_subdirectory(unittests)
endif()
add_subdirectory(include/tclap)
