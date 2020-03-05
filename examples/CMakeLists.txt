SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")

SET(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
SET(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

function(default_opts target)
target_compile_options(${target} PRIVATE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Weffc++>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)
endfunction(default_opts)

# Check we don't define any hard symbols in the headers
add_executable(test-hard test-hard-1.cpp test-hard-2.cpp)
target_include_directories(test-hard PUBLIC ../include/)
default_opts(test-hard)

file(GLOB TEST_FILES test[0-9]*.cpp)
foreach(file ${TEST_FILES})
             get_filename_component(file_basename ${file} NAME_WE)
             add_executable(${file_basename} ${file})
             target_include_directories(${file_basename} PUBLIC ../include/)
	     default_opts(${file_basename})
endforeach()
