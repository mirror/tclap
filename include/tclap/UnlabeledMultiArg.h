
/****************************************************************************** 
 * 
 *  file:  UnlabeledMultiArg.h
 * 
 *  Copyright (c) 2003, Michael E. Smoot.
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


#ifndef __MULTIPLE_UNLABELED_ARGUMENT_HH__
#define __MULTIPLE_UNLABELED_ARGUMENT_HH__

#include <string>
#include <vector>
#include <sstream>
#include <tclap/Visitor.h>

using namespace std;

namespace TCLAP {

/**
 * Just like a MultiArg, except that the arguments are unlabeled.  Basically,
 * this Arg will slurp up everything that hasn't been matched to another 
 * Arg.
 */
template<class T>
class UnlabeledMultiArg : public MultiArg<T>
{
	public:
		
		/**
		 * Constructor.  
		 * \param name - The name of the Arg. Note that this is used for
		 * identification, not as a long flag.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param typeDesc - A short, human readable description of the
		 * type that this object expects.  This is used in the generation
		 * of the USAGE statement.  The goal is to be helpful to the end user
		 * of the program.
		 * \param ignoreable - Whether or not this argument can be ignored
		 * using the "--" flag.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		UnlabeledMultiArg( const string& name,
				           const string& desc,
				           const string& typeDesc,
						   bool ignoreable = false,
				           Visitor* v = NULL );

		/**
		 * Constructor.  
		 * \param name - The name of the Arg. Note that this is used for
		 * identification, not as a long flag.
		 * \param desc - A description of what the argument is for or
		 * does.
		 * \param allowed - A vector of type T that where the values in the
		 * vector are the only values allowed for the arg.
		 * \param ignoreable - Whether or not this argument can be ignored
		 * using the "--" flag.
		 * \param v - An optional visitor.  You probably should not
		 * use this unless you have a very good reason.
		 */
		UnlabeledMultiArg( const string& name,
				           const string& desc,
				           const vector<T>& allowed,
						   bool ignoreable = false,
				           Visitor* v = NULL );

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
		 * Returns the a short id string.  Used in the usage.
		 * \param val - value to be used.
		 */
		virtual string shortID(const string& val="val") const;

		/**
		 * Returns the a long id string.  Used in the usage.
		 * \param val - value to be used.
		 */
		virtual string longID(const string& val="val") const;

		/**
		 * Opertor ==.
		 * \param a - The Arg to be compared to this.
		 */
		virtual bool operator==(const Arg& a) const;

		/**
		 * Pushes this to back of list rather than front.
		 * \param argList - The list this should be added to.
		 */
		virtual void addToList( list<Arg*>& argList ) const;
};

template<class T>
UnlabeledMultiArg<T>::UnlabeledMultiArg(const string& name, 
				                        const string& desc, 
					                    const string& typeDesc,
										bool ignoreable,
					                    Visitor* v)
: MultiArg<T>("", name, desc,  false, typeDesc, v)
{ 
	_ignoreable = ignoreable;
};

template<class T>
UnlabeledMultiArg<T>::UnlabeledMultiArg(const string& name, 
				                        const string& desc, 
					                    const vector<T>& allowed,
										bool ignoreable,
					                    Visitor* v)
: MultiArg<T>("", name, desc,  false, allowed, v)
{ 
	_ignoreable = ignoreable;
};

template<class T>
bool UnlabeledMultiArg<T>::processArg(int *i, vector<string>& args) 
{

	if ( _hasBlanks( args[*i] ) )
		return false;

	// never ignore an unlabeled multi arg

	_extractValue( args[*i] );
	return true;
}

template<class T>
string UnlabeledMultiArg<T>::shortID(const string& val) const
{
	string id = "<" + _typeDesc + "> ...";

	return id;
}

template<class T>
string UnlabeledMultiArg<T>::longID(const string& val) const
{
	string id = "<" + _typeDesc + ">  (accepted multiple times)";

	return id;
}

template<class T>
bool UnlabeledMultiArg<T>::operator==(const Arg& a) const
{
	if ( _name == a.getName() || _description == a.getDescription() )
		return true;
	else
		return false;
}

template<class T>
void UnlabeledMultiArg<T>::addToList( list<Arg*>& argList ) const
{
	argList.push_back( (Arg*)this );
}

}

#endif
