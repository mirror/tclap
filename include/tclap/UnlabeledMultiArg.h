
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

template<class T>
class UnlabeledMultiArg : public MultiArg<T>
{
	public:

		UnlabeledMultiArg( const string& name,
				           const string& desc,
				           const string& typeDesc,
						   bool ignoreable = false,
				           Visitor* v = NULL );

		virtual bool processArg(int* i, vector<string>& args); 

		virtual string shortID(const string& val="val") const;
		virtual string longID(const string& val="val") const;
		virtual bool operator==(const Arg& a) const;

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
bool UnlabeledMultiArg<T>::processArg(int *i, vector<string>& args) 
{
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

}

#endif
