
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

void CmdLine::_constructor()
{ 
	Arg::setDelimiter( _delimiter );

	SwitchArg* help = new SwitchArg("h","help",
					                "Displays usage information and exits.",
									false, new HelpVisitor( this ) );
	add( *help );

	SwitchArg* vers = new SwitchArg("v","version", 
					                "Displays version information and exits.",
									false, new VersionVisitor( this ) );
	add( *vers );

	SwitchArg* ignore  = new SwitchArg(Arg::flagStartString, 
				Arg::ignoreNameString,
               "Ignores the rest of the labeled arguments following this flag.",
			   false, new IgnoreRestVisitor() );
	add( *ignore );

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
	if ( find(_argList.begin(),_argList.end(), a) != _argList.end() ) 
	{
		cerr << "ADD ERROR:  Argument with same flag/name already exists: "
			 << a->toString() << "  Ignoring!" << endl;
		return;
	}

	if ( a->getFlag() == "" )
		_argList.push_back( a );
	else
		_argList.push_front( a );

	if ( a->isRequired() ) _numRequired++;	

}

void CmdLine::version(int exitVal)
{
	cout << endl << _progName << "  version: " << _version << endl << endl;
	exit( exitVal );
}


void CmdLine::usage( int exitVal )
{
	cout << endl << "USAGE: " << endl << endl << "    " << _progName ;

	_xorHandler.shortUsage();

	for (ArgIterator it = _argList.begin(); it != _argList.end(); it++)
		if ( !_xorHandler.contains( (*it) ) )
			cout << " " << (*it)->shortID();

	cout << endl << endl << "Where: " << endl << endl;

	_xorHandler.longUsage();

	for (ArgIterator it = _argList.begin(); it != _argList.end(); it++)
		if ( !_xorHandler.contains( (*it) ) )
			cout << "   " << (*it)->longID() << endl << "     " 
				 << (*it)->getDescription() << endl << endl;

	cout << endl << endl << _message << endl << endl;
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

		usage(1);
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
}
