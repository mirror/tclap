#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <string>

/**
 * \brief Runs a command with given parameters and compares its output to
 * stdout with the contents of a given reference file.
 * \details A temporary file will be used to catch the stdout/stderr output of
 * the command.
 * \return The program returns code 0 if both files compare equal, or a nonzero
 * value indicating the type of error.
 */
int main(int argc, char *argv[]) {
  if (argc != 4 && argc != 3)
    return 1; // Error: We need 3 parameters: reference file, command,
              // parameters

  /* Execute command and capture stdout/stderr. */
  std::string tmp = std::tmpnam(NULL);
  std::string cmd = std::string(argv[2]);
  if (argc == 4) {
    cmd += ' ';
    cmd += argv[3];
  }
  cmd += " > " + tmp + " 2>&1";
  std::system(cmd.c_str());

  /* Compare against contents of reference file. */
  std::ifstream f_tmp(tmp, std::ifstream::binary | std::ifstream::ate);
  std::ifstream f_ref(argv[1], std::ifstream::binary | std::ifstream::ate);
  if (f_tmp.fail() || f_ref.fail()) {
    f_tmp.close();
    std::remove(tmp.c_str());
    return 2; // One of the files fail.
  }
  if (f_tmp.tellg() != f_ref.tellg()) {
    f_tmp.close();
    std::remove(tmp.c_str());
    return 3; // Files have different sizes.
  }
  f_tmp.seekg(0, std::ifstream::beg);
  f_ref.seekg(0, std::ifstream::beg);
  bool bEqual = std::equal(std::istreambuf_iterator<char>(f_tmp.rdbuf()),
                           std::istreambuf_iterator<char>(),
                           std::istreambuf_iterator<char>(f_ref.rdbuf()));
  f_tmp.close();
  std::remove(tmp.c_str());
  return bEqual ? 0 : 4; // 4 = Files to not compare equal.
}
