cmake_minimum_required(VERSION 3.10)

project(TCLAP VERSION 1.4.0)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(config.h.in config.h)

add_library(tclap INTERFACE)
target_include_directories(tclap INTERFACE include/)

add_subdirectory(examples)
add_subdirectory(tests)
