
/****************************************************************************** 
 * 
 *  file:  ValueArg.h
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


#ifndef __VALUE_ARGUMENT_HH__
#define __VALUE_ARGUMENT_HH__

#include <string>
#include <vector>
#include <sstream>
#include <tclap/Visitor.h>
#include <tclap/Arg.h>

using namespace std;

namespace TCLAP {

/**
 * The basic argument that parses a value.
 * This is a template class, which means the type T defines the type
 * that a given object will attempt to parse when the flag/name is matched
 * on the command line.  Note that a ValueArg does not necessarily have to
 * have a flag specified, making this an unlabled argument. 
 */
template<class T>
class ValueArg : public Arg
{
	protected:

		/**
		 * The value parsed from the command line.
		 * Can be of any type, as long as the >> operator for the type
		 * is defined.
		 */
		T _value;

		/**
		 * Extracts the value at position i from the argv list.
		 */
		void _extractValue( int i, char** argv );
  
	public:

		/**
		 * Labeled ValueArg constructor.
		 * You could conceivably call this constructor with a blank flag, 
		 * but that would make you a bad person.  It would also cause
		 * an exception to be thrown.   If you want an unlabeled argument, 
		 * use the other constructor.
		 */
		ValueArg(const string& flag, 
				 const string& name, 
			     const string& desc, 
				 bool req, 
				 T value,
				 Visitor* v = NULL);

		/**
		 * Unlabeled ValueArg constructor.
		 */
		ValueArg(const string& name, 
			     const string& desc, 
				 T value,
				 Visitor* v = NULL); 

		/**
		 * Destructor.
		 */ 
		~ValueArg();

		/**
		 * Handles the processing of the argument.
		 * This re-implements the Arg version of this method to set the
		 * _value of the argument appropriately.  It knows the difference
		 * between labeled and unlabeled.
		 * \param int* i - Pointer the the current argument in the list.
		 * \param int argc - Number of arguments. Passed in from main().
		 * \param char** argv - List of strings. Passed in from main().
		 */
		virtual bool processArg(int* i, int argc, char** argv); 

		/**
		 * Returns the value of the argument.
		 */
		T& getValue() ;
};


/**
 * Labeled constructor implementation.
 */
template<class T>
ValueArg<T>::ValueArg(const string& flag, 
				      const string& name, 
					  const string& desc, 
					  bool req, 
					  T val,
					  Visitor* v)
: Arg(flag, name, desc, req, true, v),
  _value( val )
{ 
	if ( _flag == "" )
		throw( ArgException( "No flag specified for labeled ValueArg!",
							 toString() ) );
};

/**
 * Unlabeled constructor implemenation.
 */
template<class T>
ValueArg<T>::ValueArg(const string& name, 
					  const string& desc, 
					  T val,
					  Visitor* v)
: Arg("", name, desc, true, true, v),
  _value( val )
{ };

/**
 * Destructor implementation.
 */
template<class T>
ValueArg<T>::~ValueArg() { };

/**
 * Implementation of getValue().
 */
template<class T>
T& ValueArg<T>::getValue() { return _value; };

/**
 * Implementation of processArg().
 */
template<class T>
bool ValueArg<T>::processArg(int *i, int argc, char** argv)
{
	if ( _labeled )
	{
		string flag = argv[*i];

		if ( argMatches( flag ) )
		{
			if ( _alreadySet )
				throw( ArgException("Argument already set!", toString()) );

			(*i)++;
			if (*i < argc ) 
			{
				_extractValue( *i, argv);
				
				_alreadySet = true;

				_checkWithVisitor();

				return true;
			}
			else
				throw( ArgException("Missing a value for this argument!",
									 toString() ) );

		}	
		else
			return false;
	}
	else
	{
		if ( _alreadySet )
			return false;

		if ( *i < argc )
		{
			_extractValue( *i, argv );
			_alreadySet = true;
			return true;
		}
		else
			throw( ArgException("Missing a value for this argument!", 
									toString()));	
	}
}

/**
 * Implementation of _extractValue.
 */
template<class T>
void ValueArg<T>::_extractValue(int i, char** argv)
{
	string ss(argv[i]);
	istringstream is(ss);
	is >> _value;
	if ( is.fail() ) 
		throw( ArgException("Couldn't read argument value!", toString() ) );
}

}
#endif
