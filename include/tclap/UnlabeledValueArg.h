
/****************************************************************************** 
 * 
 *  file:  UnlabeledValueArg.h
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


#ifndef __UNLABELED_VALUE_ARGUMENT_HH__
#define __UNLABELED_VALUE_ARGUMENT_HH__

#include <string>
#include <vector>
#include <sstream>
#include <tclap/Visitor.h>
#include <tclap/Arg.h>
#include <tclap/ValueArg.h>

using namespace std;

namespace TCLAP {

/**
 * The basic unlabeled argument that parses a value.
 * This is a template class, which means the type T defines the type
 * that a given object will attempt to parse when an UnlabeledValueArg
 * is reached in the list of args that the CmdLine iterates over.
 */
template<class T>
class UnlabeledValueArg : public ValueArg<T>
{
	public:

		/**
		 * UnlabeledValueArg constructor.
		 * Note that this constructor does not have a required flag. Any 
		 * unlabeled argument added to the CmdLine is by default required.
		 * If you want optional, unlabeled arguments then use an 
		 * UnlabeledMultiArg.
		 * \param name - A one word name for the argument.  Can be
		 * used as a long flag on the command line.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param value - The default value assigned to this argument if it
		 * is not present on the command line.
		 * \param typeDesc - A short, human readable description of the
		 * type that this object expects.  This is used in the generation
		 * of the USAGE statement.  The goal is to be helpful to the end user
		 * of the program.
		 * \param ignoreable - Allows you to specify that this argument can be
		 * ignored if the '--' flag is set.  This defaults to false (cannot
		 * be ignored) and should  generally stay that way unless you have 
		 * some special need for certain arguments to be ignored.
		 * \param v - Optional Vistor.  You should leave this blank unless
		 * you have a very good reason.
		 */
		UnlabeledValueArg(const string& name, 
			              const string& desc, 
				          T value,
				          const string& typeDesc,
						  bool ignoreable = false,
				          Visitor* v = NULL); 


		/**
		 * Handles the processing of the argument.
		 * This re-implements the Arg version of this method to set the
		 * _value of the argument appropriately.  Handling specific to
		 * unlabled arguments.
		 * \param i - Pointer the the current argument in the list.
		 * \param args - Mutable list of strings. 
		 */
		virtual bool processArg(int* i, vector<string>& args); 

		/**
		 * Overrides shortID for specific behavior.
		 */
		virtual string shortID(const string& val="val") const;

		/**
		 * Overrides longID for specific behavior.
		 */
		virtual string longID(const string& val="val") const;

		/**
		 * Overrides operator== for specific behavior.
		 */
		virtual bool operator==(const Arg& a ) const;

		/**
		 * Instead of pushing to the front of list, push to the back.
		 * \param argList - The list to add this to.
		 */
		virtual void addToList( list<Arg*>& argList ) const;
};

/**
 * Constructor implemenation.
 */
template<class T>
UnlabeledValueArg<T>::UnlabeledValueArg(const string& name, 
					  const string& desc, 
					  T val,
					  const string& typeDesc,
					  bool ignoreable,
					  Visitor* v)
: ValueArg<T>("", name, desc, true, val, typeDesc, v)
{ 
	_ignoreable = ignoreable;
};

/**
 * Implementation of processArg().
 */
template<class T>
bool UnlabeledValueArg<T>::processArg(int *i, vector<string>& args) 
{
	
	if ( _alreadySet )
		return false;
	
	if ( _hasBlanks( args[*i] ) )
		return false;

	// never ignore an unlabeled arg
	
	_extractValue( args[*i] );
	_alreadySet = true;
	return true;
}

/**
 * Overriding shortID for specific output.
 */
template<class T>
string UnlabeledValueArg<T>::shortID(const string& val) const
{
	string id = "<" + _typeDesc + ">";

	return id;
}

/**
 * Overriding longID for specific output.
 */
template<class T>
string UnlabeledValueArg<T>::longID(const string& val) const
{
	// Ideally we would like to be able to use RTTI to return the name
	// of the type required for this argument.  However, g++ at least, 
	// doesn't appear to return terribly useful "names" of the types.  
	string id = "<" + _typeDesc + ">";

	return id;	
}

/**
 * Overriding operator== for specific behavior.
 */
template<class T>
bool UnlabeledValueArg<T>::operator==(const Arg& a ) const
{
	if ( _name == a.getName() || _description == a.getDescription() )
		return true;
	else
		return false;
}

template<class T>
void UnlabeledValueArg<T>::addToList( list<Arg*>& argList ) const
{
	argList.push_back( (Arg*)this );
}

}
#endif
