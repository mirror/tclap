
/****************************************************************************** 
 * 
 *  file:  MultiArg.h
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


#ifndef __MULTIPLE_ARGUMENT_HH__
#define __MULTIPLE_ARGUMENT_HH__

#include <string>
#include <vector>
#include <sstream>
#include <tclap/Visitor.h>

using namespace std;

namespace TCLAP {

/**
 * An argument that allows multiple values of type T to be specified.  Very
 * similar to a ValueArg, except a vector of values will be returned
 * instead of just one.
 */
template<class T>
class MultiArg : public Arg
{
	protected:

		/**
		 * The list of values parsed from the CmdLine.
		 */
		vector<T> _values;

		/**
		 * The description of type T to be used in the usage.
		 */
		string _typeDesc;

		/**
		 * Extracts the value from the string.
		 * Attempts to parse string as type T, if this fails an exception
		 * is thrown.
		 * \param val - The string to be read.
		 */
		void _extractValue( const string& val ); 
  
	public:

		/**
		 * Constructor.
		 * \param flag - The one character flag that identifies this
		 * argument on the command line.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 * line.
		 * \param typeDesc - A short, human readable description of the
		 * type that this object expects.  This is used in the generation
		 * of the USAGE statement.  The goal is to be helpful to the end user
		 * of the program.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		MultiArg( const string& flag,
				  const string& name,
				  const string& desc,
				  bool req,
				  const string& typeDesc,
				  Visitor* v = NULL);

		/**
		 * Destructor.
		 */
		~MultiArg();

		/**
		 * Handles the processing of the argument.
		 * This re-implements the Arg version of this method to set the
		 * _value of the argument appropriately.  It knows the difference
		 * between labeled and unlabeled.
		 * \param i - Pointer the the current argument in the list.
		 * \param args - Mutable list of strings. Passed from main().
		 */
		virtual bool processArg(int* i, vector<string>& args); 

		/**
		 * Returns a vector of type T containing the values parsed from
		 * the command line.
		 */
		const vector<T>& getValue() ;

		/**
		 * Returns the a short id string.  Used in the usage. 
		 * \param val - value to be used.
		 */
		virtual string shortID(const string& val="val") const;

		/**
		 * Returns the a long id string.  Used in the usage. 
		 * \param val - value to be used.
		 */
		virtual string longID(const string& val="val") const;

};

/**
 *
 */
template<class T>
MultiArg<T>::MultiArg(const string& flag, 
				      const string& name,
				      const string& desc,
					  bool req,
					  const string& typeDesc,
				      Visitor* v)
: Arg( flag, name, desc, req, true, v ),
  _typeDesc( typeDesc )
{ };

/**
 *
 */
template<class T>
MultiArg<T>::~MultiArg() { };

/**
 *
 */
template<class T>
const vector<T>& MultiArg<T>::getValue() { return _values; };

/**
 *
 */
template<class T>
bool MultiArg<T>::processArg(int *i, vector<string>& args) 
{
	if ( _ignoreable && Arg::ignoreRest() )
		return false;

	if ( _hasBlanks( args[*i] ) )
		return false;

	string flag = args[*i];
	string value = "";

	trimFlag( flag, value );

	if ( argMatches( flag ) )
	{
		if ( Arg::_delimiter != ' ' && value == "" )
			throw( ArgException( "Couldn't find delimiter for this argument!",
           	                          toString() ) );

		if ( value == "" )
		{
			(*i)++;
			if ( (unsigned int)*i < args.size() )
				_extractValue( args[*i] );
			else
				throw( ArgException("Missing a value for this argument!",
           	                          toString() ) );
		}
		else
			_extractValue( value );

		return true;
	}
	else
		return false;
}

/**
 *
 */
template<class T>
void MultiArg<T>::_extractValue( const string& val )
{
	T temp;
	istringstream is(val);
	is >> temp; 
	if ( is.fail() ) 
		throw( ArgException("Couldn't read argument value!", toString()));

	_values.push_back(temp);

	_checkWithVisitor();
}

/**
 *
 */
template<class T>
string MultiArg<T>::shortID(const string& val) const
{
	string id = Arg::shortID(_typeDesc) + " ... ";

	return id;
}

/**
 *
 */
template<class T>
string MultiArg<T>::longID(const string& val) const
{
	string id = Arg::longID(_typeDesc) + "  (accepted multiple times)";

	return id;
}

}

#endif
