
/****************************************************************************** 
 * 
 *  file:  CmdLine.h
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

#ifndef __COMMANDLINE_HH__
#define __COMMANDLINE_HH__

//
// Explanation of dumb naming.  Originally this file was used as the generic
// include to use the tclap library.  However, this introduced a few weird
// bugs related to g++.  Thus, this file has been renamed, and CmdLine.h
// just contains the files needed to use the lib.
//

#include <tclap/Arg.h>
#include <tclap/SwitchArg.h>
#include <tclap/Visitor.h>
#include <tclap/XorHandler.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <iomanip>
#include <algorithm>

using namespace std;

namespace TCLAP {

/**
 * The base class that manages the command line definition and passes
 * along the parsing to the appropriate Arg classes.
 */
class CmdLine
{
	protected:

		/**
		 * The list of arguments that will be tested against the
		 * command line.
		 */
		list<Arg*> _argList;

		/**
		 * The name of the program.  Set to argv[0].
		 */
		string _progName;

		/**
		 * A message used to describe the program.  Used in the usage output.
		 */
		string _message;

		/**
		 * The version to be displayed with the --version switch.
		 */
		string _version;

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
		 * Checks whether a name/flag string matches entirely matches
		 * the Arg::blankChar.  Used when multiple switches are combined
		 * into a single argument.
		 * \param s - The message to be used in the usage.
		 */
		bool _emptyCombined(const string& s);

	private:

		/**
		 * Encapsulates the code common to the constructors (which is all
		 * of it).
		 */
		void _constructor();

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
		CmdLine(const string& name, 
				const string& message,
				const string& version = "none" );

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
		CmdLine(const string& message, 
				const char delimiter = ' ',
				const string& version = "none" );

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
		void xorAdd( vector<Arg*>& xors );

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

}

// These have to be included _after_ CmdLine is declared, because
// they rely on CmdLine existing.  Don't know why I can't forward
// declare CmdLine...   this works.

#include "HelpVisitor.h"
#include "VersionVisitor.h"
#include "IgnoreRestVisitor.h"


#endif 
