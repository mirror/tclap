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
install(FILES "${PROJECT_BINARY_DIR}/tclap/TCLAPConfig.h"
  DESTINATION include/tclap
  )

add_subdirectory(docs)
add_subdirectory(examples)
add_subdirectory(tests)
add_subdirectory(include/tclap)
