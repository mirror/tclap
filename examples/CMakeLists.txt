# Check we don't define any hard symbols in the headers
add_executable(test-hard test-hard-1.cpp test-hard-2.cpp)
target_include_directories(test-hard PUBLIC ../include/)

file(GLOB TEST_FILES test[0-9]*.cpp)
foreach(file ${TEST_FILES})
             get_filename_component(file_basename ${file} NAME_WE)
             add_executable(${file_basename} ${file})
             target_include_directories(${file_basename} PUBLIC ../include/)
endforeach()
