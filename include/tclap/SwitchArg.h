
/****************************************************************************** 
 * 
 *  file:  SwitchArg.h
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


#ifndef __SWITCH_ARG_HH__
#define __SWITCH_ARG_HH__

#include <string>
#include <vector>
#include <sstream>
#include <tclap/Arg.h>
#include <tclap/ArgException.h>

namespace TCLAP {

/**
 * A simple switch argument.  If the switch is set on the command line, then
 * the getValue method will return the opposite of the default value for the
 * switch.
 */
class SwitchArg : public Arg
{
	protected:

		/**
		 * The value of the switch.
		 */
		bool _value;


	public:

        /**
		 * SwitchArg constructor.
		 * \param flag - The one character flag that identifies this
		 * argument on the command line.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param def - The default value for this Switch. 
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		SwitchArg(const std::string& flag, 
			      const std::string& name, 
			      const std::string& desc,
			      bool def,
				  Visitor* v = NULL);

				  
		/**
		 * SwitchArg constructor.
		 * \param flag - The one character flag that identifies this
		 * argument on the command line.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param parser - A CmdLine parser object to add this Arg to
		 * \param def - The default value for this Switch.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		SwitchArg(const std::string& flag, 
			      const std::string& name, 
			      const std::string& desc,
			      bool def,
				  CmdLine& parser,
				  Visitor* v = NULL);
				  
				  
		/**
		 * Destructor.
		 */
		~SwitchArg();

        /**
		 * Handles the processing of the argument.
		 * This re-implements the Arg version of this method to set the
		 * _value of the argument appropriately.
		 * \param i - Pointer the the current argument in the list.
		 * \param args - Mutable list of strings. Passed
		 * in from main().
		 */
		virtual bool processArg(int* i, std::vector<std::string>& args); 

		/**
		 * Checks a string to see if any of the chars in the string
		 * match the flag for this Switch.
		 */
		bool combinedSwitchesMatch(std::string& combined);

		/**
		 * Returns bool, whether or not the switch has been set.
		 */
		bool getValue() ;
};

}

#endif
