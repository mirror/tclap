cmake_minimum_required(VERSION 3.10)

# set the project name
project(TCLAP VERSION 1.4.0)

configure_file(config.h.in config.h)

# add_executable(test1 examples/test1.cpp)

add_library(tclap INTERFACE)
target_include_directories(tclap INTERFACE include/)

#target_include_directories(include PUBLIC
#                           "${PROJECT_BINARY_DIR}"
#                           )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(examples)
add_subdirectory(tests)
