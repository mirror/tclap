
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


#include <tclap/CmdLine.h>

namespace TCLAP {

CmdLine::CmdLine(char *progName, const string& m, const string& v )
: _progName(progName),
  _message(m),
  _version(v),
  _numRequired(0),
  _maxLength(0)
{ 
	SwitchArg* help = new SwitchArg("h","help",
					                "displays usage information and exits",
									false, new HelpVisitor( this ) );
	add( *help );

	SwitchArg* vers = new SwitchArg("v","version", 
					                "displays version information and exits",
									false, new VersionVisitor( this ) );
	add( *vers );
}

void CmdLine::add( Arg& a ) 
{ 
	if ( find(_argList.begin(),_argList.end(), &a) != _argList.end() ) 
	{
		cerr << "ADD ERROR:  Argument with same flag/name already exists: "
			 << a.toString() << "  Ignoring!" << endl;
		return;
	}

	if ( a.isLabeled() )
		_argList.push_front( &a ); 
	else
		_argList.push_back( &a );

	_maxLength = max( _maxLength, (int)((a.getName()).length()) );
	if ( a.isRequired() ) _numRequired++;	

}

void CmdLine::version(int exitVal)
{
	cout << endl << _progName << "  version: " << _version << endl << endl;
	exit( exitVal );
}


void CmdLine::usage( int exitVal )
{
	cout << endl << "USAGE: " << endl << endl << "    " << _progName ;

	for (ArgIterator it = _argList.begin(); it != _argList.end(); it++)
	{

		cout << " ";
		if ( !(*it)->isRequired() ) cout << "[";
		if ( (*it)->isLabeled() )
			cout << "-" << ((*it))->getFlag(); 
		if ( (*it)->isValueRequired() ) 
		{
			if ( (*it)->isLabeled() ) cout << " ";
			cout << (*it)->getName();
		}
		if ( !(*it)->isRequired() ) cout << "]";
	}

	cout << endl << endl << "Where: " << endl << endl;

	for (ArgIterator it = _argList.begin(); it != _argList.end(); it++)
	{
		cout.setf(ios::left);

		string s; 

		if ( !(*it)->isRequired() ) s += "[";
		else s += " ";

		if ( (*it)->isLabeled() )
			s = s + "-" + (*it)->getFlag(); 

		if ( (*it)->isValueRequired() ) 
		{
			if ( (*it)->isLabeled() ) s += " ";
			s += (*it)->getName();
		}
			
		if ( !(*it)->isRequired() ) s += "]";

		cout << "  " << setw(_maxLength + 5) << s.c_str() << "  = " 
		     << (*it)->getDescription() << endl;
	}

	cout << endl << endl << _message << endl << endl;
	exit( exitVal );
}

void CmdLine::parse(int argc, char** argv)
{
	try {

	int requiredCount = 0;

  	for (int i = 1; i < argc; i++)
	{
		bool matched = false;
		for (ArgIterator it = _argList.begin(); it != _argList.end(); it++)
        {
			if ( (*it)->processArg( &i, argc, argv ) )
			{
				if ( (*it)->isRequired() ) requiredCount++;	
				matched = true;
				break;
			}
        }

		if ( !matched )
			throw( ArgException("Couldn't find match for argument",argv[i]));
    }

	if ( requiredCount < _numRequired )
		throw( ArgException("One or more required arguments missing!") );

	if ( requiredCount > _numRequired )
		throw( ArgException("Too many arguments!") );

	} catch ( ArgException e )
	{
		cerr << "PARSE ERROR: for argument:   " << e.argId() << endl
			 << "             " << e.error() << endl << endl;

		usage(1);
	}
}

}
