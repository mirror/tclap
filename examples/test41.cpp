#include "tclap/CmdLine.h"

using namespace TCLAP;

int main(int argc, char **argv)
{
  CmdLine cmd("");
  ValueArg<int> arg0("i","int", "tests int arg", false, 4711, "integer", cmd);
  AliasArg arg1("j", "jnt", arg0, cmd);

  cmd.parse(argc, argv);
}
