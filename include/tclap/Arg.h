
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
	private: 

		/**
		 * Indicates whether the rest of the arguments should be ignored.
		 */
		static bool _ignoreRest;


	protected:

		/**
		 * The delimiter that separates an argument flag/name from the
		 * value.
		 */
		static char _delimiter; 

		/** 
		 * The single char flag used to identify the argument.
		 * This value (preceded by a dash {-}), can be used to identify 
		 * an argument on the command line.  The _flag can be blank, 
		 * in fact this is how unlabeled args work.  Unlabeled args must
		 * override appropriate functions to get correct handling. Note 
		 * that the _flag does NOT include the dash as part of the flag.
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
		 * Label to be used in usage description.  Normally set to 
		 * "required", but can be changed when necessary.
		 */
		string _requireLabel;

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
		 * A pointer to a vistitor object.
		 * The visitor allows special handling to occur as soon as the
		 * argument is matched.  This defaults to NULL and should not
		 * be used unless absolutely necessary.
		 */
		Visitor* _visitor;

		/**
		 * Whether this argument can be ignored, if desired.
		 */
		bool _ignoreable;

		/**
		 * Indicates that the arg was set as part of an XOR and not on the
		 * command line.
		 */
		bool _xorSet;

		/**
		 * Performs the special handling described by the Vistitor.
		 */
		void _checkWithVisitor() const;

	public:
		
		/**
		 * Begin ignoring arguments since the "--" argument was specified.
		 */
		static void beginIgnoring() { Arg::_ignoreRest = true; }
		
		/**
		 * Whether to ignore the rest.
		 */
		static bool ignoreRest() { return Arg::_ignoreRest; }
		
		/**
		 * The char used as a place holder when SwitchArgs are combined.
		 * Currently set to '*', which shouldn't cause many problems since
		 * *'s are expanded by most shells on the command line.  
		 */
		static const char blankChar; 
		
		/**
		 * The char that indicates the beginning of a flag.  Currently '-'.
		 */
		static const char flagStartChar; 
		
		/**
		 * The sting that indicates the beginning of a flag.  Currently "-".
		 * Should be identical to flagStartChar.
		 */
		static const string flagStartString;
		
		/**
		 * The sting that indicates the beginning of a name.  Currently "--".
		 * Should be flagStartChar twice.
		 */
		static const string nameStartString;

		/**
		 * Sets the delimiter for all arguments.
		 * \param c - The character that delimits flags/names from values.
		 */
		static void setDelimiter( char c ) { Arg::_delimiter = c; }

		/**
		 * Primary constructor.
		 * \param flag - The flag identifying the argument.
		 * \param name - The name identifying the argument.
		 * \param desc - The description of the argument, used in the usage.
		 * \param req - Whether the argument is required.
		 * \param valreq - Whether the a value is required for the argument.
		 * \param v - The visitor checked by the argument. Defaults to NULL.
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
		 * \param a - The Arg to be copied. 
		 */
		Arg(const Arg& a);

		/**
		 * Operator =.
		 * Assignment operator.
		 * \param a - The Arg to be assigned to this.
		 */
		Arg& operator=(const Arg& a);

		/**
		 * Destructor.
		 */
		virtual ~Arg();

		/**
		 * Processes the argument.
		 * This is the method that handles the parsing and value assignment
		 * of the string on the command line.  This implementation just
		 * emits that an argument has matched and is being ignored. This 
		 * should never really be used, any subclass should implement its
		 * own version of processArg.
		 * \param i - Pointer the the current argument in the list.
		 * \param args - Mutable list of strings. What is 
		 * passed in from main.
		 */
		virtual bool processArg(int *i, vector<string>& args); 


		/**
		 * Operator ==.
		 * Equality operator. Must be virtual to handle unlabeled args.
		 * \param a - The Arg to be compared to this.
		 */
		virtual bool operator==(const Arg& a);

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
		string getDescription() const;

		/**
		 * Indicates whether the argument is required.
		 */
		bool isRequired() const;

		/**
		 * Sets _required to true. This is used by the XorHandler.
		 * You really have no reason to ever use it.
		 */
		void forceRequired();

		/**
		 * Sets the _alreadySet value to true.  This is used by the XorHandler.
		 * You really have no reason to ever use it.
		 */
		void xorSet();

		/**
		 * Indicates whether a value must be specified for argument.
		 */
		bool isValueRequired() const;

		/**
		 * Indicates whether the argument has already been set.  Only true
		 * if the arg has been matched on the command line.
		 */
		bool isSet() const;

		/**
		 * Indicates whether the argument can be ignored, if desired. 
		 */
		bool isIgnoreable() const;

		/**
		 * A method that tests whether a string matches this argument.
		 * This is generally called by the processArg() method.  This
		 * method could be re-implemented by a child to change how 
		 * arguments are specified on the command line.
		 * \param s - The string to be compared to the flag/name to determine
		 * whether the arg matches.
		 */
		virtual bool argMatches( const string& s ) const;

		/**
		 * Returns a simple string representation of the argument.
		 * Primarily for debugging.
		 */
		virtual string toString() const;

		/**
		 * Returns a short ID for the usage.
		 * \param valueId - The value used in the id.
		 */
		virtual string shortID( const string& valueId = "val" ) const;

		/**
		 * Returns a long ID for the usage.
		 * \param valueId - The value used in the id.
		 */
		virtual string longID( const string& valueId = "val" ) const;

		/**
		 * Trims a value off of the flag.
		 * \param flag - The string from which the flag and value will be 
		 * trimmed. Contains the flag once the value has been trimmed. 
		 * \param value - Where the value trimmed from the string will
		 * be stored.
		 */
		virtual void trimFlag( string& flag, string& value ) const;

		/**
		 * Checks whether a given string has blank chars, indicating that
		 * it is a combined SwitchArg.  If so, return true, otherwise return
		 * false.
		 * \param s - string to be checked.
		 */
		bool _hasBlanks( const string& s ) const;

		/**
		 * Sets the requireLabel. Used by XorHandler.  You shouldn't ever
		 * use this.
		 * \param s - Set the requireLabel to this value.
		 */
		void setRequireLabel( const string& s );

};

/**
 * Typedef of a list iterator.
 */
typedef list<Arg*>::iterator ArgIterator;
typedef vector<Arg*>::iterator ArgVectorIterator;

}

#endif

