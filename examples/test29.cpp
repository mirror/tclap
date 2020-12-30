#include "tclap/CmdLine.h"
#include <vector>
#include <string>

using namespace TCLAP;
using namespace std;

// https://sourceforge.net/p/tclap/bugs/30/
int main(int argc, char** argv) {
  CmdLine cmd("test empty argv");
  std::vector<string> args;
  cmd.parse(args);
}
