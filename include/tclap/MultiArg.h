
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

template<class T>
class MultiArg : public Arg
{
	protected:

		vector<T> _values;

		string _typeDesc;

		void _extractValue(int i, vector<string>& args); 
  
	public:

		MultiArg( const string& flag,
				  const string& name,
				  const string& desc,
				  bool req,
				  const string& typeDesc,
				  Visitor* v = NULL);

		~MultiArg();

		virtual bool processArg(int* i, vector<string>& args); 

		const vector<T>& getValue() ;

		virtual string shortID(const string& val="val") const;
		virtual string longID(const string& val="val") const;

};


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

template<class T>
MultiArg<T>::~MultiArg() { };

template<class T>
const vector<T>& MultiArg<T>::getValue() { return _values; };

template<class T>
bool MultiArg<T>::processArg(int *i, vector<string>& args) 
{
	if ( _ignoreable && Arg::ignoreRest() )
		return false;

	if ( argMatches( args[*i] ) )
	{
		(*i)++;
		if ( *i < args.size() )
		{
			_extractValue( *i, args );
			return true;
		}
		else
			throw( ArgException("Missing a value for this argument!",
                                     toString() ) );
	}
	else
		return false;
}

template<class T>
void MultiArg<T>::_extractValue(int i, vector<string>& args)
{
	T temp;
	istringstream is(args[i]);
	is >> temp; 
	if ( is.fail() ) 
		throw( ArgException("Couldn't read argument value!", toString()));

	_values.push_back(temp);

	_checkWithVisitor();
}

template<class T>
string MultiArg<T>::shortID(const string& val) const
{
	string id = Arg::shortID(_typeDesc) + " ... ";

	return id;
}

template<class T>
string MultiArg<T>::longID(const string& val) const
{
	string id = Arg::longID(_typeDesc) + "  (accepted multiple times)";

	return id;
}

}

#endif
