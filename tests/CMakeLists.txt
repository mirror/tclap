SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")

find_package(Python3)
enable_testing()

file(GLOB TEST_FILES test[0-9]*.py)
foreach(file ${TEST_FILES})
  get_filename_component(file_basename ${file} NAME_WE)
  add_test(NAME ${file_basename}
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/simple_test.py
    ${file_basename})
endforeach()
