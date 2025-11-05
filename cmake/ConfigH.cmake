include(CheckCXXSourceCompiles)
check_cxx_source_compiles("#include <strstream>
int main() { std::istrstream iss; }" TCLAP_HAVE_STRSTREAM)

check_cxx_source_compiles("#include <sstream>
int main() { std::istringstream iss; }" TCLAP_HAVE_SSTREAM)

set(GENERATED_CONFIG_NAME "TCLAPConfig.h")
set(GENERATED_CONFIG_BUILD_DIR "${PROJECT_BINARY_DIR}/tclap")
set(GENERATED_CONFIG_BUILD_PATH "${GENERATED_CONFIG_BUILD_DIR}/${GENERATED_CONFIG_NAME}")

configure_file(config.h.in "${GENERATED_CONFIG_BUILD_PATH}")

