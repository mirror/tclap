// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

/****************************************************************************** 
 * 
 *  file:  CmdLineInterface.h
 * 
 *  Copyright (c) 2003, Michael E. Smoot .
 *  Copyright (c) 2004, Michael E. Smoot, Daniel Aarno.
 *  All rights reserved.
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

#ifndef TCLAP_COMMANDLINE_INTERFACE_H
#define TCLAP_COMMANDLINE_INTERFACE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

#include <tclap/ArgContainer.h>

namespace TCLAP {

class Arg;
class ArgGroup;
class CmdLineOutput;

/**
 * The base class that manages the command line definition and passes
 * along the parsing to the appropriate Arg classes.
 */
class CmdLineInterface : public ArgContainer
{
	public:

		/**
		 * Destructor
		 */
		virtual ~CmdLineInterface() {}

        /**
         * Adds an argument. Ownership is not transfered.
         * @param a - Argument to be added.
         * @retval A reference to this so that add calls can be chained
         */
        virtual ArgContainer& add(Arg& a)=0;

        /**
         * Adds an argument. Ownership is not transfered.
         * @param a - Argument to be added. 
         * @retval A reference to this so that add calls can be chained
         */
        virtual ArgContainer& add(Arg* a)=0;
    
        /**
		 * Adds an argument group to the list of arguments to be parsed.
		 *
		 * All arguments in the group are added and the ArgGroup
		 * object will validate that the input matches its
		 * constraints.
		 *
		 * @param args - Argument group to be added.
         * @retval A reference to this so that add calls can be chained
		 */
		virtual ArgContainer &add(ArgGroup &args)=0;

		/**
		 * Add two Args that will be xor'd.  
		 * If this method is used, add does
		 * not need to be called.
		 * \param a - Argument to be added and xor'd. 
		 * \param b - Argument to be added and xor'd. 
		 * \deprecated Use ArgGroups instead.
		 */
		virtual void xorAdd( Arg& a, Arg& b )=0;

		/**
		 * Add a list of Args that will be xor'd.  If this method is used, 
		 * add does not need to be called.
		 * \param xors - List of Args to be added and xor'd. 
		 * \deprecated Use ArgGroups instead.
		 */
		virtual void xorAdd( const std::vector<Arg*>& xors )=0;

		/**
		 * Parses the command line.
		 * \param argc - Number of arguments.
		 * \param argv - Array of arguments.
		 */
		virtual void parse(int argc, const char * const * argv)=0;

        /**
         * Parses the command line.
         * \param args - A vector of strings representing the args. 
         * args[0] is still the program name.
         */
        void parse(std::vector<std::string>& args);

		/**
		 * Returns the CmdLineOutput object.
		 */
		virtual CmdLineOutput* getOutput()=0;

		/**
		 * \param co - CmdLineOutput object that we want to use instead. 
		 */
		virtual void setOutput(CmdLineOutput* co)=0;

		/**
		 * Returns the version string.
		 */
		virtual std::string& getVersion()=0;

		/**
		 * Returns the program name string.
		 */
		virtual std::string& getProgramName()=0;

		/**
		 * Returns the argList. 
		 */
		virtual std::list<Arg*>& getArgList()=0;

		/**
		 * Returns the list of ArgGroups.
		 */
		virtual std::list<ArgGroup*>& getArgGroups()=0;

		/**
		 * Returns the delimiter string.
		 */
		virtual char getDelimiter()=0;

		/**
		 * Returns the message string.
		 */
		virtual std::string& getMessage()=0;

		/**
		 * Indicates whether or not the help and version switches were created
		 * automatically.
		 */
		virtual bool hasHelpAndVersion()=0;

		/** 
		 * Resets the instance as if it had just been constructed so that the
		 * instance can be reused. 
		 */
		virtual void reset()=0;
};

} //namespace


#endif 
