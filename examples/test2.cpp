

#include <tclap/CmdLine.h>
#include <iostream>
#include <string>

using namespace TCLAP; 

int _intTest;
float _floatTest;
bool _boolTest;
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
		 << "for bool we got : " << _boolTest << endl;

}


void parseOptions(int argc, char** argv)
{
	try {

	CmdLine cmd(argv[0], "this is a message", "0.99" );

	// 
	// Define arguments
	//

	SwitchArg btest("B","existTest", "exist Test", false);
	cmd.add( btest );

	ValueArg<string> stest("s", "stringTest", "string test", true, "homer");
	cmd.add( stest );

	ValueArg<int> itest("i", "intTest", "integer test", true, 5);
	cmd.add( itest );
							 
	ValueArg<double> ftest("f", "floatTest", "float test", false, 3.7);
	cmd.add( ftest );

	ValueArg<string> utest("unTest","unlabeld test", "default");
	cmd.add( utest );

	MultiArg<string> mtest("file names");
	cmd.add( mtest );

	//
	// Parse the command line.
	//
	cmd.parse(argc,argv);



	//
	// Set variables
	//
	_intTest = itest.getValue();
	_floatTest = ftest.getValue();
	_stringTest = stest.getValue();
	_boolTest = btest.getValue();
	_utest = utest.getValue();

	vector<string> v = mtest.getValue();
	for ( int i = 0; i < v.size(); i++ ) 
		cout << i << "  " <<  v[i] << endl;

	} catch ( ArgException e )
	{ cout << "ERROR: " << e.error() << " " << e.argId() << endl; }
}



