

#include <tclap/CmdLine.h>
#include <iostream>
#include <string>

using namespace TCLAP; 

int _intTest;
float _floatTest;
bool _boolTestA;
bool _boolTestB;
bool _boolTestC;
string _stringTest;
string _utest;

void parseOptions(int argc, char** argv);

int main(int argc, char** argv)
{

	parseOptions(argc,argv);

	cout << "for float we got : " << _floatTest << endl
		 << "for int we got : " << _intTest<< endl
		 << "for string we got : " << _stringTest<< endl
		 << "for ulabeled we got : " << _utest << endl
		 << "for bool A we got : " << _boolTestA << endl
		 << "for bool B we got : " << _boolTestB << endl
		 << "for bool C we got : " << _boolTestC << endl;

}


void parseOptions(int argc, char** argv)
{
	try {

	CmdLine cmd(argv[0], "this is a message", "0.99" );

	// 
	// Define arguments
	//

	SwitchArg btest("B","existTest B", "exist Test B", false);
	cmd.add( btest );

	ValueArg<string> stest("s", "stringTest", "string test", true, "homer", 
					       "string");
	cmd.add( stest );

	UnlabeledValueArg<string> utest("unTest","unlabeld test", 
					                "default","string");
	cmd.add( utest );

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

	vector<int> vi = itest.getValue();
	for ( int i = 0; i < vi.size(); i++ ) 
		cout << "[-i] " << i << "  " <<  vi[i] << endl;

	vector<string> v = mtest.getValue();
	for ( int i = 0; i < v.size(); i++ ) 
		cout << "[  ] " << i << "  " <<  v[i] << endl;

	} catch ( ArgException e )
	{ cout << "ERROR: " << e.error() << " " << e.argId() << endl; }
}



