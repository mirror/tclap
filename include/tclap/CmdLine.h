
/****************************************************************************** 
 * 
 *  file:  CmdLine.h
 * 
 *  Copyright (c) 2003, Michael E. Smoot .
 *  Copyright (c) 2004, Michael E. Smoot, Daniel Aarno.
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

#ifndef TCLAP_CMDLINE_H
#define TCLAP_CMDLINE_H

#include <tclap/SwitchArg.h>
#include <tclap/UnlabeledValueArg.h>
#include <tclap/UnlabeledMultiArg.h>

#include <tclap/XorHandler.h>
#include <tclap/HelpVisitor.h>
#include <tclap/VersionVisitor.h>
#include <tclap/IgnoreRestVisitor.h>

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <ostream>
#include <cstdio>
#include <cstdarg>
#include <iomanip>
#include <algorithm>

namespace TCLAP {

/**
 * The base class that manages the command line definition and passes
 * along the parsing to the appropriate Arg classes.
 */
class CmdLine : public CmdLineInterface
{
	protected:

		/**
		 * The list of arguments that will be tested against the
		 * command line.
		 */
		std::list<Arg*> _argList;

		/**
		 * The name of the program.  Set to argv[0].
		 */
		std::string _progName;

		/**
		 * A message used to describe the program.  Used in the usage output.
		 */
		std::string _message;

		/**
		 * The version to be displayed with the --version switch.
		 */
		std::string _version;

		/**
		 * The number of arguments that are required to be present on 
		 * the command line. This is set dynamically, based on the 
		 * Args added to the CmdLine object.
		 */
		int _numRequired;

		/**
		 * The character that is used to separate the argument flag/name 
		 * from the value.  Defaults to ' ' (space).
		 */
		char _delimiter;

		/**
		 * The handler that manages xoring lists of args.
		 */
		XorHandler _xorHandler;

		/**
		 * A list of Args to be explicitly deleted when the destructor
		 * is called.  At the moment, this only includes the three default
		 * Args.
		 */
		std::list<Arg*> _argDeleteOnExitList;

		/**
		 * A list of Visitors to be explicitly deleted when the destructor
		 * is called.  At the moment, these are the Vistors created for the
		 * default Args.
		 */
		std::list<Visitor*> _visitorDeleteOnExitList;
		
		/**
		 * Checks whether a name/flag string matches entirely matches
		 * the Arg::blankChar.  Used when multiple switches are combined
		 * into a single argument.
		 * \param s - The message to be used in the usage.
		 */
		bool _emptyCombined(const std::string& s);

		/**
		 * Writes a brief usage message with short args.
		 * \param os - The stream to write the message to.
		 */
		void _shortUsage( std::ostream& os );

		/**
		 * Writes a longer usage message with long and short args, 
		 * provides descriptions and prints message.
		 * \param os - The stream to write the message to.
		 */
		void _longUsage( std::ostream& os );

	private:

		/**
		 * Encapsulates the code common to the constructors (which is all
		 * of it).
		 */
		void _constructor();

		/**
		 * Perform a delete ptr; operation on ptr when this object is deleted.
		 */
		void deleteOnExit(Arg* ptr);

		/**
		 * Perform a delete ptr; operation on ptr when this object is deleted.
		 */
		void deleteOnExit(Visitor* ptr);

	public:

		/**
		 * Command line constructor. DEPRECATED!!!  This is here to maintain
		 * backwards compatibility with earlier releases.  Note that the
		 * program name will be overwritten with argv[0].  The delimiter
		 * used is ' ' (as before).
		 * \param name - The program name - will be overwritten with argv[0].
		 * \param message - The message to be used in the usage output.
		 * \param version - The version number to be used in the
		 * --version switch.
		 */
		CmdLine(const std::string& name, 
				const std::string& message,
				const std::string& version = "none" );

		/**
		 * Command line constructor. Defines how the arguments will be
		 * parsed.
		 * \param message - The message to be used in the usage
		 * output.
		 * \param delimiter - The character that is used to separate
		 * the argument flag/name from the value.  Defaults to ' ' (space).
		 * \param version - The version number to be used in the
		 * --version switch.
		 */
		CmdLine(const std::string& message, 
				const char delimiter = ' ',
				const std::string& version = "none" );
		
		/**
		 * Deletes any resources allocated by a CmdLine object.
		 */
		~CmdLine();

		/**
		 * Adds an argument to the list of arguments to be parsed.
		 * \param a - Argument to be added. 
		 */
		void add( Arg& a );

		/**
		 * An alternative add.  Functionally identical.
		 * \param a - Argument to be added. 
		 */
		void add( Arg* a );

		/**
		 * Add two Args that will be xor'd.  If this method is used, add does
		 * not need to be called.
		 * \param a - Argument to be added and xor'd. 
		 * \param b - Argument to be added and xor'd. 
		 */
		void xorAdd( Arg& a, Arg& b );

		/**
		 * Add a list of Args that will be xor'd.  If this method is used, 
		 * add does not need to be called.
		 * \param xors - List of Args to be added and xor'd. 
		 */
		void xorAdd( std::vector<Arg*>& xors );

		/**
		 * Prints the usage to stdout and exits.
		 * \param exitVal - Value to exit with. 
		 */
		void usage( int exitVal = 0 );

		/**
		 * Prints the version to stdout and exits.
		 * \param exitVal - Value to exit with. 
		 */
		void version( int exitVal = 0 );

		/**
		 * Parses the command line.
		 * \param argc - Number of arguments.
		 * \param argv - Array of arguments.
		 */
		void parse(int argc, char** argv);
};


///////////////////////////////////////////////////////////////////////////////
//Begin CmdLine.cpp
///////////////////////////////////////////////////////////////////////////////

inline CmdLine::CmdLine(const std::string& n, const std::string& m, const std::string& v )
: _progName(n),
  _message(m),
  _version(v),
  _numRequired(0),
  _delimiter(' ')
{ 
	_constructor();
}

inline CmdLine::CmdLine(const std::string& m, char delim, const std::string& v )
: _progName("not_set_yet"),
  _message(m),
  _version(v),
  _numRequired(0),
  _delimiter(delim)
{
	_constructor();
}

inline CmdLine::~CmdLine()
{
	std::list<Arg*>::iterator argIter;
	std::list<Visitor*>::iterator visIter;
  
	for( argIter = _argDeleteOnExitList.begin(); 
		 argIter != _argDeleteOnExitList.end(); 
		 ++argIter)
		delete *argIter;
  
	for( visIter = _visitorDeleteOnExitList.begin(); 
		 visIter != _visitorDeleteOnExitList.end(); 
		 ++visIter) 
		delete *visIter;
}

inline void CmdLine::_constructor()
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
	SwitchArg* ignore  = new SwitchArg(Arg::flagStartString(), 
					   Arg::ignoreNameString(),
			   "Ignores the rest of the labeled arguments following this flag.",
					   false, v);
	add( *ignore );
	deleteOnExit(ignore);
	deleteOnExit(v);
}

inline void CmdLine::xorAdd( std::vector<Arg*>& ors )
{
	_xorHandler.add( ors );

	for (ArgVectorIterator it = ors.begin(); it != ors.end(); it++)
	{
		(*it)->forceRequired();
		(*it)->setRequireLabel( "OR required" );

		add( *it );
	}
}

inline void CmdLine::xorAdd( Arg& a, Arg& b ) 
{
    std::vector<Arg*> ors;
    ors.push_back( &a );
    ors.push_back( &b );
	xorAdd( ors );
}

inline void CmdLine::add( Arg& a ) 
{ 
	add( &a );
}

inline void CmdLine::add( Arg* a ) 
{ 
	for( ArgIterator iter = _argList.begin(); iter != _argList.end(); iter++ ) 
		if ( *a == *(*iter) ) 
			throw( ArgException( "Argument with same flag/name already exists!",
			                     a->longID() ) );

	a->addToList( _argList );

	if ( a->isRequired() ) _numRequired++;	
}

inline void CmdLine::version(int exitVal)
{
	std::cout << std::endl << _progName << "  version: " << _version << std::endl << std::endl;
	exit( exitVal );
}

inline void CmdLine::_shortUsage( std::ostream& os ) 
{
	std::string s = _progName + " " + _xorHandler.shortUsage();

	for (ArgIterator it = _argList.begin(); it != _argList.end(); it++)
		if ( !_xorHandler.contains( (*it) ) )
			s += " " + (*it)->shortID();

	spacePrint( os, s, 75, 3, (int)(_progName.length()) + 2 );
}

inline void CmdLine::_longUsage( std::ostream& os )
{
	_xorHandler.printLongUsage( os );

	for (ArgIterator it = _argList.begin(); it != _argList.end(); it++)
		if ( !_xorHandler.contains( (*it) ) )
		{
			spacePrint( os, (*it)->longID(), 75, 3, 3 ); 
			spacePrint( os, (*it)->getDescription(), 75, 5, 0 ); 
			os << std::endl;
		}

	os << std::endl;
	spacePrint( os, _message, 75, 3, 0 );
}

inline void CmdLine::usage( int exitVal )
{
	std::cout << std::endl << "USAGE: " << std::endl << std::endl; 

	_shortUsage( std::cout );

	std::cout << std::endl << std::endl << "Where: " << std::endl << std::endl;

	_longUsage( std::cout );

	std::cout << std::endl; 

	exit( exitVal );
}

inline void CmdLine::parse(int argc, char** argv)
{
	try {

	_progName = argv[0]; 

	// this step is necessary so that we have easy access to mutable strings.
	std::vector<std::string> args;
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
		std::cerr << "PARSE ERROR: " << e.argId() << std::endl
			 << "             " << e.error() << std::endl << std::endl;

		std::cerr << "Brief USAGE: " << std::endl;

		_shortUsage( std::cerr );	

		std::cerr << std::endl << "For complete USAGE and HELP type: " 
			 << std::endl << "   " << _progName << " --help" << std::endl << std::endl;

		exit(1);
	}
}

inline bool CmdLine::_emptyCombined(const std::string& s)
{
	if ( s[0] != Arg::flagStartChar() )
		return false;

	for ( int i = 1; (unsigned int)i < s.length(); i++ )
		if ( s[i] != Arg::blankChar() )
			return false;

	return true;
}

inline void CmdLine::deleteOnExit(Arg* ptr)
{
	_argDeleteOnExitList.push_back(ptr);
}

inline void CmdLine::deleteOnExit(Visitor* ptr)
{
	_visitorDeleteOnExitList.push_back(ptr);
}

///////////////////////////////////////////////////////////////////////////////
//End CmdLine.cpp
///////////////////////////////////////////////////////////////////////////////



} //namespace TCLAP
#endif 
