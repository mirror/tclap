
/****************************************************************************** 
 * 
 *  file:  Arg.h
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


#ifndef __ARGUMENT_HH__
#define __ARGUMENT_HH__

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <tclap/ArgException.h>
#include <tclap/Visitor.h>

using namespace std;

namespace TCLAP {

/** 
 * A base class that defines the essential data for all arguments.
 * This is not an abstract class, although it can't really be used
 * because the processArg() method just emits a warning.  Arg, or one
 * of its existing children, should be subclassed for new behavior. 
 */
class Arg
{
	protected:

		/** 
		 * The single char flag used to identify the argument.
		 * This value (preceded by a dash {-}), can be used to identify 
		 * an argument on the command line.  The _flag can be blank, 
		 * in fact this is how unlabeled
		 * ValueArgs work.  If the _flag is blank, the _labeled valued
		 * should be set to false. Note that the _flag does NOT include
		 * the dash as part of the flag.
		 */
		string _flag;

		/**
		 * A single work namd indentifying the argument.
		 * This value (preceded by two dashed {--}) can also be used 
		 * to identify an argument on the command line.  Note that the
		 * _name does NOT include the two dashes as part of the _name. The
		 * _name cannot be blank.
		 */
		string _name;

		/**
		 * Description of the argument. 
		 */
		string _description;

		/** 
		 * Indicating whether the argument is required.
		 */
		bool _required;

		/**
		 * Indicates whether a value is required for the argument.
		 * Note that the value may be required but the argument/value
		 * combination may not be, as specified by _required.
		 */
		bool _valueRequired;

		/**
		 * Indicates whether the argument has been set.
		 * Indicates that a value on the command line has matched the
		 * name/flag of this argument and the values have been set accordingly.
		 */
		bool _alreadySet;

		/**
		 * Indicates whether the _flag is set or not.
		 * If the argument doesn't require a flag then the argument is
		 * handled differently.
		 */
		bool _labeled;

		/**
		 * A pointer to a vistitor object.
		 * The visitor allows special handling to occur as soon as the
		 * argument is matched.  This defaults to NULL and should not
		 * be used unless absolutely necessary.
		 */
		Visitor* _visitor;

		/**
		 * Performs the special handling described by the Vistitor.
		 */
		void _checkWithVisitor() const;
  
	public:

		/**
		 * Primary constructor.
		 */
		Arg(const string& flag, 
			const string& name, 
			const string& desc, 
			bool req, 
			bool valreq,
			Visitor* v = NULL);

		/**
		 * Null constructor.
		 * Everything set to null/blank/0 values.
		 */
		Arg();

		/**
		 * Copy constructor.
		 */
		Arg(const Arg&);

		/**
		 * Operator =.
		 * Assignment operator.
		 */
		Arg& operator=(const Arg&);

		/**
		 * Destructor.
		 */
		~Arg();


		/**
		 * Processes the argument.
		 * This is the method that handles the parsing and value assignment
		 * of the string on the command line.  This implementation just
		 * emits that an argument has matched and is being ignored. This 
		 * should never really be used, any subclass should implement its
		 * own version of processArg.
		 * \param int* i - Pointer the the current argument in the list.
		 * \param int argc - Number of arguments. Passed in from main().
		 * \param char** argv - List of strings. Passed in from main().
		 */
		virtual bool processArg(int *i, int argc, char** argv); 


		/**
		 * Operator ==.
		 * Equality operator.
		 */
		bool operator==(const Arg&);

		/**
		 * Returns the argument flag.
		 */
		const string& getFlag() const;

		/**
		 * Returns the argument name.
		 */
		const string& getName() const;

		/**
		 * Returns the argument description.
		 */
		const string& getDescription() const;

		/**
		 * Indicates whether the argument is required.
		 */
		bool isRequired() const;

		/**
		 * Indicates whether a value must be specified for argument.
		 */
		bool isValueRequired() const;

		/**
		 * Indicates whether the argument has already been set.
		 */
		bool isAlreadySet() const;

		/**
		 * Indicates whether the _flag value is blank or not.
		 * If the _flag is blank, the argument is considered unlabeled.
		 */
		bool isLabeled() const;

		/**
		 * A method that tests whether a string matches this argument.
		 * This is generally called by the processArg() method.  This
		 * method could be re-implemented by a child to change how 
		 * arguments are specified on the command line.
		 */
		virtual bool argMatches( const string& s ) const;

		/**
		 * Returns a simple string representation of the argument.
		 * Primarily for debugging.
		 */
		string toString() const;
};

/**
 * Typedef of a list iterator.
 */
typedef list<Arg*>::iterator ArgIterator;

}

#endif

