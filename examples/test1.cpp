#include <string>
#include <tclap/CmdLine.h>

using namespace TCLAP;

int main(int argc, char** argv)
{
	// Wrap everything in a try block.  Do this every time, 
	// because exceptions will be thrown for problems. 
	try {  

	// Define the command line object.
	CmdLine cmd(argv[0], "Command description message", "0.9");

	// Define a value argument and add it to the command line.
	ValueArg<string> nameArg("n","name","Name to print",true,"homer");
	cmd.add( nameArg );

	// Define a switch and add it to the command line.
	SwitchArg caseSwitch("u","upperCase","Print in upper case", false);
	cmd.add( caseSwitch );

	// Parse the args.
	cmd.parse( argc, argv );

	// Get the value parsed by each arg. 
	string name = nameArg.getValue();
	bool upperCase = caseSwitch.getValue();

	// Do what you intend too...
	if ( upperCase )
		transform(name.begin(),name.end(),name.begin(),::toupper);
	else
		transform(name.begin(),name.end(),name.begin(),::tolower);

	cout << "My name is " << name << endl;

	} catch (ArgException e)  // catch any exceptions
	{ cerr << "error: " << e.error() << " for arg " << e.argId() << endl; }
}

