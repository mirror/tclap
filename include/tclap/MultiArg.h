
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


#ifndef TCLAP_MULTIPLE_ARGUMENT_H
#define TCLAP_MULTIPLE_ARGUMENT_H

#include <string>
#include <vector>
#include <sstream>
#include <tclap/Visitor.h>
#include <tclap/CommandLine.h>

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
		std::vector<T> _values;

        /**
		 * A list of allowed values.
		 * A list of values allowed for this argument. If the value parsed
		 * for this arg is not found in this list, then an exception is
		 * thrown.  If the list is empty, then any value is allowed.
		 */
		std::vector<T> _allowed;

		/**
		 * The description of type T to be used in the usage.
		 */
		std::string _typeDesc;

		/**
		 * Extracts the value from the string.
		 * Attempts to parse string as type T, if this fails an exception
		 * is thrown.
		 * \param val - The string to be read.
		 */

		void _extractValue( const std::string& val ); 

        /**
		 * Checks to see if parsed value is in allowed list.
		 * \param val - value parsed (only used in output).
		 */
		void _checkAllowed( const std::string& val );

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
		MultiArg( const std::string& flag,
				  const std::string& name,
				  const std::string& desc,
				  bool req,
				  const std::string& typeDesc,
				  Visitor* v = NULL);

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
		 * \param parser - A CmdLine parser object to add this Arg to
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		 MultiArg( const std::string& flag, 
				   const std::string& name,
				   const std::string& desc,
				   bool req,
				   const std::string& typeDesc,
				   CmdLine& parser,
				   Visitor* v = NULL );
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
		 * \param allowed - A vector of type T that where the values in the
		 * vector are the only values allowed for the arg.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		MultiArg( const std::string& flag,
				  const std::string& name,
				  const std::string& desc,
				  bool req,
				  const std::vector<T>& allowed,
				  Visitor* v = NULL );
		  
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
		 * \param allowed - A vector of type T that where the values in the
		 * vector are the only values allowed for the arg.
		 * \param parser - A CmdLine parser object to add this Arg to
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		MultiArg( const std::string& flag, 
				  const std::string& name,
				  const std::string& desc,
				  bool req,
				  const std::vector<T>& allowed,
				  CmdLine& parser,
				  Visitor* v = NULL );
		  
		/**
		 * Handles the processing of the argument.
		 * This re-implements the Arg version of this method to set the
		 * _value of the argument appropriately.  It knows the difference
		 * between labeled and unlabeled.
		 * \param i - Pointer the the current argument in the list.
		 * \param args - Mutable list of strings. Passed from main().
		 */
		virtual bool processArg(int* i, std::vector<std::string>& args); 

		/**
		 * Returns a vector of type T containing the values parsed from
		 * the command line.
		 */
		const std::vector<T>& getValue();

		/**
		 * Returns the a short id string.  Used in the usage. 
		 * \param val - value to be used.
		 */
		virtual std::string shortID(const std::string& val="val") const;

		/**
		 * Returns the a long id string.  Used in the usage. 
		 * \param val - value to be used.
		 */
		virtual std::string longID(const std::string& val="val") const;

		/**
		 * Once we've matched the first value, then the arg is no longer
		 * required.
		 */
		virtual bool isRequired() const;

	private:

		/**
         * Common initialization code for constructors with allowed vectors.
         */
		void allowedInit();
};

/**
 *
 */
template<class T>
void MultiArg<T>::allowedInit()
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
 *
 */
template<class T>
MultiArg<T>::MultiArg(const std::string& flag, 
				      const std::string& name,
				      const std::string& desc,
					  bool req,
					  const std::string& typeDesc,
				      Visitor* v)
: Arg( flag, name, desc, req, true, v ),
  _typeDesc( typeDesc )
{ }

template<class T>
MultiArg<T>::MultiArg(const std::string& flag, 
				      const std::string& name,
				      const std::string& desc,
					  bool req,
					  const std::string& typeDesc,
					  CmdLine& parser,
				      Visitor* v)
: Arg( flag, name, desc, req, true, v ),
  _typeDesc( typeDesc )
{ 
	parser.add( this );
}

/**
 *
 */
template<class T>
MultiArg<T>::MultiArg(const std::string& flag, 
				      const std::string& name,
				      const std::string& desc,
					  bool req,
					  const std::vector<T>& allowed,
				      Visitor* v)
: Arg( flag, name, desc, req, true, v ),
  _allowed( allowed )
{ 
	allowedInit();
}

template<class T>
MultiArg<T>::MultiArg(const std::string& flag, 
				      const std::string& name,
				      const std::string& desc,
					  bool req,
					  const std::vector<T>& allowed,
					  CmdLine& parser,
				      Visitor* v)
: Arg( flag, name, desc, req, true, v ),
  _allowed( allowed )
{ 
	allowedInit();
	parser.add( this );
}

/**
 *
 */
template<class T>
const std::vector<T>& MultiArg<T>::getValue() { return _values; }

/**
 *
 */
template<class T>
bool MultiArg<T>::processArg(int *i, std::vector<std::string>& args) 
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

		_checkWithVisitor();
		return true;
	}
	else
		return false;
}

/**
 *
 */
template<class T>
void MultiArg<T>::_extractValue( const std::string& val )
{
	T temp;
	std::istringstream is(val);

	int valuesRead = 0;
	while ( is.good() )
	{
		if ( is.peek() != EOF )
			is >> temp; 
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


	_values.push_back(temp);

	_checkAllowed( val );

}

/**
 * Specialization to handle strings with spaces in them. This is needed
 * because there is no way to tell operator>> to ignore spaces.
 */
template<>
void MultiArg<std::string>::_extractValue( const std::string& val )
{
	_values.push_back( val );

	_checkAllowed( val );
}

/**
 * Checks to see if the value parsed is in the allowed list.
 */
template<class T>
void MultiArg<T>::_checkAllowed( const std::string& val )
{
	if ( _allowed.size() > 0 )
		if ( find(_allowed.begin(),_allowed.end(),_values.back()) 
						== _allowed.end() )
			throw( ArgException( "Couldn't find '" + val +
                                 "' in allowed list.", toString() ) );
}

/**
 *
 */
template<class T>
std::string MultiArg<T>::shortID(const std::string& val) const
{
	std::string id = Arg::shortID(_typeDesc) + " ... ";

	return id;
}

/**
 *
 */
template<class T>
std::string MultiArg<T>::longID(const std::string& val) const
{
	std::string id = Arg::longID(_typeDesc) + "  (accepted multiple times)";

	return id;
}

/**
 * Once we've matched the first value, then the arg is no longer
 * required.
 */
template<class T>
bool MultiArg<T>::isRequired() const
{
	if ( _required )
	{
		if ( _values.size() > 1 )
			return false;
		else
			return true;
	}
	else
		return false;

}

}

#endif
