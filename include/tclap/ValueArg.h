
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

namespace TCLAP {

/**
 * The basic labeled argument that parses a value.
 * This is a template class, which means the type T defines the type
 * that a given object will attempt to parse when the flag/name is matched
 * on the command line.  While there is nothing stopping you from creating
 * an unflagged ValueArg, it is unwise and would cause significant problems.
 * Instead use an UnlabeledValueArg.
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
		 * A list of allowed values.
		 * A list of values allowed for this argument. If the value parsed
		 * for this arg is not found in this list, then an exception is 
		 * thrown.  If the list is empty, then any value is allowed.
		 */
		std::vector<T> _allowed;

		/**
		 * A human readable description of the type to be parsed.
		 * This is a hack, plain and simple.  Ideally we would use RTTI to
		 * return the name of type T, but until there is some sort of
		 * consistent support for human readable names, we are left to our
		 * own devices.
		 */
		std::string _typeDesc;

		/**
		 * Extracts the value from the string.
		 * Attempts to parse string as type T, if this fails an exception
		 * is thrown.
		 * \param val - value to be parsed. 
		 */
		void _extractValue( const std::string& val ); 

		/**
		 * Checks to see if parsed value is in allowed list.
		 * \param val - value parsed (only used in output). 
		 */
		void _checkAllowed( const std::string& val );

	public:

		/**
		 * Labeled ValueArg constructor.
		 * You could conceivably call this constructor with a blank flag, 
		 * but that would make you a bad person.  It would also cause
		 * an exception to be thrown.   If you want an unlabeled argument, 
		 * use the other constructor.
		 * \param flag - The one character flag that identifies this
		 * argument on the command line.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 * line.
		 * \param value - The default value assigned to this argument if it
		 * is not present on the command line.
		 * \param typeDesc - A short, human readable description of the
		 * type that this object expects.  This is used in the generation
		 * of the USAGE statement.  The goal is to be helpful to the end user
		 * of the program.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		ValueArg( const std::string& flag, 
				  const std::string& name, 
			      const std::string& desc, 
				  bool req, 
				  T value,
				  const std::string& typeDesc,
				  Visitor* v = NULL);
				 
				 
		 /**
		 * Labeled ValueArg constructor.
		 * You could conceivably call this constructor with a blank flag, 
		 * but that would make you a bad person.  It would also cause
		 * an exception to be thrown.   If you want an unlabeled argument, 
		 * use the other constructor.
		 * \param flag - The one character flag that identifies this
		 * argument on the command line.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 * line.
		 * \param value - The default value assigned to this argument if it
		 * is not present on the command line.
		 * \param typeDesc - A short, human readable description of the
		 * type that this object expects.  This is used in the generation
		 * of the USAGE statement.  The goal is to be helpful to the end user
		 * of the program.
		 * \param parser - A CmdLine parser object to add this Arg to
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		ValueArg( const std::string& flag, 
				  const std::string& name, 
			      const std::string& desc, 
				  bool req, 
				  T value,
				  const std::string& typeDesc,
				  CmdLine& parser,
				  Visitor* v = NULL );
				 
		 /**
		 * Labeled ValueArg constructor.
		 * You could conceivably call this constructor with a blank flag, 
		 * but that would make you a bad person.  It would also cause
		 * an exception to be thrown.   If you want an unlabeled argument, 
		 * use the other constructor.
		 * \param flag - The one character flag that identifies this
		 * argument on the command line.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 * line.
		 * \param value - The default value assigned to this argument if it
		 * is not present on the command line.
		 * \param allowed - A vector of type T that where the values in the 
		 * vector are the only values allowed for the arg.
		 * \param parser - A CmdLine parser object to add this Arg to.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		 ValueArg( const std::string& flag, 
				   const std::string& name, 
				   const std::string& desc, 
				   bool req, 
				   T value,
				   const std::vector<T>& allowed,
				   CmdLine& parser,
				   Visitor* v = NULL );
					  
		/**
		 * Labeled ValueArg constructor.
		 * You could conceivably call this constructor with a blank flag, 
		 * but that would make you a bad person.  It would also cause
		 * an exception to be thrown.   If you want an unlabeled argument, 
		 * use the other constructor.
		 * \param flag - The one character flag that identifies this
		 * argument on the command line.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param req - Whether the argument is required on the command
		 * line.
		 * \param value - The default value assigned to this argument if it
		 * is not present on the command line.
		 * \param allowed - A vector of type T that where the values in the 
		 * vector are the only values allowed for the arg.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		ValueArg( const std::string& flag, 
				  const std::string& name, 
			      const std::string& desc, 
				  bool req, 
				  T value,
				  const std::vector<T>& allowed,
				  Visitor* v = NULL );

		/**
		 * Handles the processing of the argument.
		 * This re-implements the Arg version of this method to set the
		 * _value of the argument appropriately.  It knows the difference
		 * between labeled and unlabeled.
		 * \param i - Pointer the the current argument in the list.
		 * \param args - Mutable list of strings. Passed 
		 * in from main().
		 */
		virtual bool processArg(int* i, std::vector<std::string>& args); 

		/**
		 * Returns the value of the argument.
		 */
		T& getValue() ;

		/**
		 * Specialization of shortID.
		 * \param val - value to be used.
		 */
		virtual std::string shortID(const std::string& val = "val") const;

		/**
		 * Specialization of longID.
		 * \param val - value to be used.
		 */
		virtual std::string longID(const std::string& val = "val") const;

	private: 
		
		/**
		 * Common initialization code for constructors with allowed vectors.
		 */
		void allowedInit();

};


template<class T>
void ValueArg<T>::allowedInit()
{
	for ( unsigned int i = 0; i < _allowed.size(); i++ )
	{
		std::ostringstream os;
		os << _allowed[i];

		std::string temp( os.str() ); 

		if ( i > 0 )
			_typeDesc += "|";
		_typeDesc += temp;
	}
}

/**
 * Constructor implementation.
 */
template<class T>
ValueArg<T>::ValueArg(const std::string& flag, 
				      const std::string& name, 
					  const std::string& desc, 
					  bool req, 
					  T val,
					  const std::string& typeDesc,
					  Visitor* v)
: Arg(flag, name, desc, req, true, v),
  _value( val ),
  _typeDesc( typeDesc )
{ }

template<class T>
ValueArg<T>::ValueArg(const std::string& flag, 
				      const std::string& name, 
					  const std::string& desc, 
					  bool req, 
					  T val,
					  const std::string& typeDesc,
					  CmdLine& parser,
					  Visitor* v)
: Arg(flag, name, desc, req, true, v),
  _value( val ),
  _typeDesc( typeDesc )
{ 
	parser.add( this );
}

/**
 * Constructor with allowed list. 
 */
template<class T>
ValueArg<T>::ValueArg(const std::string& flag, 
				      const std::string& name, 
					  const std::string& desc, 
					  bool req, 
					  T val,
					  const std::vector<T>& allowed,
					  Visitor* v)
: Arg(flag, name, desc, req, true, v),
  _value( val ),
  _allowed( allowed )
{ 
	allowedInit();
}

template<class T>
ValueArg<T>::ValueArg(const std::string& flag, 
				      const std::string& name, 
					  const std::string& desc, 
					  bool req, 
					  T val,
					  const std::vector<T>& allowed,
					  CmdLine& parser,
					  Visitor* v)
: Arg(flag, name, desc, req, true, v),
  _value( val ),
  _allowed( allowed )
{ 
	allowedInit();
	parser.add( this );
}


/**
 * Implementation of getValue().
 */
template<class T>
T& ValueArg<T>::getValue() { return _value; }

/**
 * Implementation of processArg().
 */
template<class T>
bool ValueArg<T>::processArg(int *i, std::vector<std::string>& args)
{
	if ( _ignoreable && Arg::ignoreRest() )
		return false;

	if ( _hasBlanks( args[*i] ) )
		return false;

	std::string flag = args[*i];

	std::string value = "";
	trimFlag( flag, value );

	if ( argMatches( flag ) )
	{
		if ( _alreadySet )
			throw( ArgException("Argument already set!", toString()) );

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
				
		_alreadySet = true;
		_checkWithVisitor();
		return true;
	}	
	else
		return false;
}

/**
 * Implementation of _extractValue.
 */
template<class T>
void ValueArg<T>::_extractValue( const std::string& val ) 
{
	std::istringstream is(val);

	int valuesRead = 0;
	while ( is.good() )
	{
		if ( is.peek() != EOF )
			is >> _value;
		else
			break;
		valuesRead++;
	}

	if ( is.fail() ) 
		throw( ArgException("Couldn't read argument value from string '" +
							 val + "'", toString() ) );

	if ( valuesRead > 1 )
		throw( ArgException("More than one valid value parsed from string '" +
							val + "'", toString() ) );

	_checkAllowed( val );
}

/**
 * Specialization for string.  This is necessary because istringstream
 * operator>> is not able to ignore spaces...  meaning -x "X Y" will only 
 * read 'X'... and thus the specialization.
 */
template<>
void ValueArg<std::string>::_extractValue( const std::string& val ) 
{
	_value = val;
	_checkAllowed( val );
}

/**
 * Checks to see if the value parsed is in the allowed list.
 */
template<class T>
void ValueArg<T>::_checkAllowed( const std::string& val )
{
	if ( _allowed.size() > 0 )
		if ( find(_allowed.begin(),_allowed.end(),_value) == _allowed.end() )
			throw( ArgException( "Couldn't find '" + val + 
							     "' in allowed list.", toString() ) );
}

/**
 * Implementation of shortID.
 */
template<class T>
std::string ValueArg<T>::shortID(const std::string& val) const
{
	return Arg::shortID( _typeDesc );	
}

/**
 * Implementation of longID.
 */
template<class T>
std::string ValueArg<T>::longID(const std::string& val) const
{
	return Arg::longID( _typeDesc );	
}

}
#endif
