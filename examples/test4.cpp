

#include <tclap/CmdLine.h>
#include <iostream>
#include <string>

using namespace TCLAP; 
using namespace std; 


// This exemplifies how the CmdLine class can be overridden to provide
// user defined output.
class MyCmdLine : public CmdLine
{
	public:

        MyCmdLine(const std::string& name,
                const std::string& message,
                const std::string& version = "none" )
		: CmdLine(name,message,version) { }

		MyCmdLine(const std::string& message,
	            const char delimiter = ' ',
	             const std::string& version = "none" )
		: CmdLine(message,delimiter,version) { }

		virtual void failure(const ArgException& e)
		{
			cerr << "My special failure message for: " << endl
			     << e.what() << endl; 
			exit(1);
		}
};


bool _boolTestB;
bool _boolTestA;
string _stringTest;

void parseOptions(int argc, char** argv);

int main(int argc, char** argv)
{

	parseOptions(argc,argv);

	cout << "for string we got : " << _stringTest<< endl
		 << "for bool B we got : " << _boolTestB << endl
		 << "for bool A we got : " << _boolTestA << endl;

}


void parseOptions(int argc, char** argv)
{
	try {

	MyCmdLine cmd("this is a message", ' ', "0.99" );

	// 
	// Define arguments
	//

	SwitchArg btest("B","sB", "exist Test B", false);
	SwitchArg atest("A","sA", "exist Test A", false);

	ValueArg<string> stest("s", "Bs", "string test", true, "homer", 
					       "string");
	cmd.add( stest );
	cmd.add( btest );
	cmd.add( atest );

	//
	// Parse the command line.
	//
	cmd.parse(argc,argv);


	//
	// Set variables
	//
	_stringTest = stest.getValue();
	_boolTestB = btest.getValue();
	_boolTestA = atest.getValue();


	} catch ( ArgException e )
	{ cout << "ERROR: " << e.error() << " " << e.argId() << endl; }
}



