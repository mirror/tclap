

#include <tclap/CmdLine.h>
#include <iostream>
#include <string>

using namespace TCLAP; 

string _orTest;
string _testc;
string _testd;

void parseOptions(int argc, char** argv);

int main(int argc, char** argv)
{

	parseOptions(argc,argv);

	cout << "for A OR B we got : " << _orTest<< endl
		 << "for string C we got : " << _testc << endl
		 << "for string D we got : " << _testd << endl;

}


void parseOptions(int argc, char** argv)
{
	try {

	CmdLine cmd("this is a message", ' ', "0.99" );

	// 
	// Define arguments
	//

	ValueArg<string> atest("a", "aaa", "or test a", true, "homer", "string");
	ValueArg<string> btest("b", "bbb", "or test b", true, "homer", "string");

	ValueArg<string> ctest("c", "ccc", "c test", true, "homer", "string");
	ValueArg<string> dtest("d", "ddd", "d test", false, "homer", "string");

	cmd.xorAdd( atest, btest );
	cmd.add( ctest );
	cmd.add( dtest );

	//
	// Parse the command line.
	//
	cmd.parse(argc,argv);


	//
	// Set variables
	//
	
	if ( atest.isSet() )
		_orTest = atest.getValue();
	else if ( btest.isSet() )
		_orTest = btest.getValue();
	else
		// Should never get here because TCLAP will note that one of the
		// required args above has not been set.
		throw("very bad things...");


	_testc = ctest.getValue();
	_testd = dtest.getValue();


	} catch ( ArgException e )
	{ cout << "ERROR: " << e.error() << " " << e.argId() << endl; }
}



