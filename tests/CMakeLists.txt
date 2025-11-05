set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")

# CMake added specific version-aware support in 3.12.
if(CMAKE_VERSION VERSION_LESS 3.12)
	find_package(PythonInterp 3 REQUIRED)
else()
	find_package(Python3 COMPONENTS Interpreter REQUIRED)
	set(PYTHON_EXECUTABLE "${PYTHON3_EXECUTABLE}")
endif()
enable_testing()

file(GLOB TEST_FILES test[0-9]*.py)
foreach(file ${TEST_FILES})
  get_filename_component(file_basename ${file} NAME_WE)
  add_test(NAME ${file_basename}
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/simple_test.py
    ${PYTHON_EXECUTABLE} ${file_basename})
endforeach()
