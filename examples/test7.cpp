#include <string>
#include <tclap/CmdLine.h>

using namespace TCLAP;

int main(int argc, char** argv)
{
	// Wrap everything in a try block.  Do this every time, 
	// because exceptions will be thrown for problems. 
	try {  

	// Define the command line object.
	CmdLine cmd("Command description message", ' ', "0.9");

	vector<string> allowed;
	allowed.push_back("homer");
	allowed.push_back("marge");
	allowed.push_back("bart");
	allowed.push_back("lisa");
	allowed.push_back("maggie");

	MultiArg<string> nameArg("n","name","Name to print",true,allowed);
	cmd.add( nameArg );

	vector<int> iallowed;
	iallowed.push_back(1);
	iallowed.push_back(2);
	iallowed.push_back(3);

	UnlabeledMultiArg<int> intArg("times","Number of times to print",iallowed);
	cmd.add( intArg );

	// Parse the args.
	cmd.parse( argc, argv );

	// Get the value parsed by each arg. 
	vector<int> num = intArg.getValue();

	for ( unsigned int i = 0; i < num.size(); i++ )
		cout << "Got num " << num[i] << endl;

	vector<string> name = nameArg.getValue();

	for ( unsigned int i = 0; i < name.size(); i++ )
		cout << "Got name " << name[i] << endl;
	

	} catch (ArgException e)  // catch any exceptions
	{ cerr << "error: " << e.error() << " for arg " << e.argId() << endl; }
}

