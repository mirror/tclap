

#include <tclap/CmdLine.h>
#include <iostream>
#include <string>

using namespace TCLAP; 

bool _boolTestB;
string _stringTest;
string _utest;
string _ztest;

void parseOptions(int argc, char** argv);

int main(int argc, char** argv)
{

	parseOptions(argc,argv);

	cout << "for string we got : " << _stringTest<< endl
		 << "for ulabeled one we got : " << _utest << endl
		 << "for ulabeled two we got : " << _ztest << endl
		 << "for bool B we got : " << _boolTestB << endl;

}


void parseOptions(int argc, char** argv)
{
	try {

	CmdLine cmd("this is a message", '=', "0.99" );

	// 
	// Define arguments
	//

	SwitchArg btest("B","existTest B", "exist Test B", false);
	cmd.add( btest );

	ValueArg<string> stest("s", "stringTest", "string test", true, "homer", 
					       "string");
	cmd.add( stest );

	UnlabeledValueArg<string> utest("unTest1","unlabeled test one", 
					                "default","string");
	cmd.add( utest );

	UnlabeledValueArg<string> ztest("unTest2","unlabeled test two", 
					                "default","string");
	cmd.add( ztest );

	MultiArg<int> itest("i", "intTest", "multi int test", false,"int" );
	cmd.add( itest );

	UnlabeledMultiArg<string> mtest("fileName","file names","fileNameString");
	cmd.add( mtest );
	//
	// Parse the command line.
	//
	cmd.parse(argc,argv);


	//
	// Set variables
	//
	_stringTest = stest.getValue();
	_boolTestB = btest.getValue();
	_utest = utest.getValue();
	_ztest = ztest.getValue();

	vector<int> vi = itest.getValue();
	for ( int i = 0; i < vi.size(); i++ ) 
		cout << "[-i] " << i << "  " <<  vi[i] << endl;

	vector<string> v = mtest.getValue();
	for ( int i = 0; i < v.size(); i++ ) 
		cout << "[  ] " << i << "  " <<  v[i] << endl;

	} catch ( ArgException e )
	{ cout << "ERROR: " << e.error() << " " << e.argId() << endl; }
}



