
/****************************************************************************** 
 * 
 *  file:  CmdLine.cpp
 * 
 *  Copyright (c) 2003, Michael E. Smoot .
 *  All rights reverved.
 * 
 *  See the file COPYING in the top directory of this distribution for
 *  more information.
 *  
 *  THE SOFTWARE IS PROVIDED _AS IS_, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 *  DEALINGS IN THE SOFTWARE.  
 *  
 *****************************************************************************/ 


#include <tclap/CommandLine.h>

using namespace std;

namespace TCLAP {

CmdLine::CmdLine(const string& n, const string& m, const string& v )
: _progName(n),
  _message(m),
  _version(v),
  _numRequired(0),
  _delimiter(' ')
{ 
	_constructor();
}

CmdLine::CmdLine(const string& m, char delim, const string& v )
: _progName("not_set_yet"),
  _message(m),
  _version(v),
  _numRequired(0),
  _delimiter(delim)
{
	_constructor();
}

CmdLine::~CmdLine()
{
  list<Arg*>::iterator argIter;
  list<Visitor*>::iterator visIter;
  
  for(argIter = _argDeleteOnExitList.begin(); argIter != _argDeleteOnExitList.end(); ++argIter) {
    delete *argIter;
  }
  
  for(visIter = _visitorDeleteOnExitList.begin(); visIter != _visitorDeleteOnExitList.end(); ++visIter) {
    delete *visIter;
  }
}

void CmdLine::_constructor()
{ 
	Visitor *v;
	
	Arg::setDelimiter( _delimiter );

	v = new HelpVisitor( this );
	SwitchArg* help = new SwitchArg("h","help", 
					"Displays usage information and exits.", 
					false, v);
	add( *help );
	deleteOnExit(help);
	deleteOnExit(v);
	
	v = new VersionVisitor( this );
	SwitchArg* vers = new SwitchArg("v","version", 
					"Displays version information and exits.", 
					false, v);
	add( *vers );
	deleteOnExit(vers);
	deleteOnExit(v);

	v = new IgnoreRestVisitor();
	SwitchArg* ignore  = new SwitchArg(Arg::flagStartString, 
					   Arg::ignoreNameString,
					   "Ignores the rest of the labeled arguments following this flag.",
					   false, v);
	add( *ignore );
	deleteOnExit(ignore);
	deleteOnExit(v);
}

void CmdLine::xorAdd( vector<Arg*>& ors )
{
	_xorHandler.add( ors );

	for (ArgVectorIterator it = ors.begin(); it != ors.end(); it++)
	{
		(*it)->forceRequired();
		(*it)->setRequireLabel( "OR required" );

		add( *it );
	}
}

void CmdLine::xorAdd( Arg& a, Arg& b ) 
{
    vector<Arg*> ors;
    ors.push_back( &a );
    ors.push_back( &b );
	xorAdd( ors );
}

void CmdLine::add( Arg& a ) 
{ 
	add( &a );
}

void CmdLine::add( Arg* a ) 
{ 
	for( ArgIterator iter = _argList.begin(); iter != _argList.end(); iter++ ) 
		if ( *a == *(*iter) ) 
			throw( ArgException( "Argument with same flag/name already exists!",
			                     a->longID() ) );

	a->addToList( _argList );

	if ( a->isRequired() ) _numRequired++;	
}

void CmdLine::version(int exitVal)
{
	cout << endl << _progName << "  version: " << _version << endl << endl;
	exit( exitVal );
}

void CmdLine::_shortUsage( ostream& os ) 
{
	string s = _progName + " " + _xorHandler.shortUsage();

	for (ArgIterator it = _argList.begin(); it != _argList.end(); it++)
		if ( !_xorHandler.contains( (*it) ) )
			s += " " + (*it)->shortID();

	spacePrint( os, s, 75, 3, (int)(_progName.length()) + 2 );
}

void CmdLine::_longUsage( ostream& os )
{
	_xorHandler.printLongUsage( os );

	for (ArgIterator it = _argList.begin(); it != _argList.end(); it++)
		if ( !_xorHandler.contains( (*it) ) )
		{
			spacePrint( os, (*it)->longID(), 75, 3, 3 ); 
			spacePrint( os, (*it)->getDescription(), 75, 5, 0 ); 
			os << endl;
		}

	os << endl;
	spacePrint( os, _message, 75, 3, 0 );
}

void CmdLine::usage( int exitVal )
{
	cout << endl << "USAGE: " << endl << endl; 

	_shortUsage( cout );

	cout << endl << endl << "Where: " << endl << endl;

	_longUsage( cout );

	cout << endl; 

	exit( exitVal );
}

void CmdLine::parse(int argc, char** argv)
{
	try {

	_progName = argv[0]; 

	// this step is necessary so that we have easy access to mutable strings.
	vector<string> args;
  	for (int i = 1; i < argc; i++)
		args.push_back(argv[i]);

	int requiredCount = 0;

  	for (int i = 0; (unsigned int)i < args.size(); i++)
	{
		bool matched = false;
		for (ArgIterator it = _argList.begin(); it != _argList.end(); it++)
        {
			if ( (*it)->processArg( &i, args ) )
			{
				requiredCount += _xorHandler.check( *it );
				matched = true;
				break;
			}
        }

		// checks to see if the argument is an empty combined switch ...
		// and if so, then we've actually matched it
		if ( !matched && _emptyCombined( args[i] ) )
			matched = true;

		if ( !matched && !Arg::ignoreRest() )
			throw( ArgException("Couldn't find match for argument",args[i]));
    }

	if ( requiredCount < _numRequired )
		throw( ArgException("One or more required arguments missing!") );

	if ( requiredCount > _numRequired )
		throw( ArgException("Too many arguments!") );

	} catch ( ArgException e )
	{
		cerr << "PARSE ERROR: " << e.argId() << endl
			 << "             " << e.error() << endl << endl;

		cerr << "Brief USAGE: " << endl;

		_shortUsage( cerr );	

		cerr << endl << "For complete USAGE and HELP type: " 
			 << endl << "   " << _progName << " --help" << endl << endl;

		exit(1);
	}
}

bool CmdLine::_emptyCombined(const string& s)
{
	if ( s[0] != Arg::flagStartChar )
		return false;

	for ( int i = 1; (unsigned int)i < s.length(); i++ )
		if ( s[i] != Arg::blankChar )
			return false;

	return true;
}

void CmdLine::deleteOnExit(Arg* ptr)
{
  _argDeleteOnExitList.push_back(ptr);
}

void CmdLine::deleteOnExit(Visitor* ptr)
{
  _visitorDeleteOnExitList.push_back(ptr);
}

}
