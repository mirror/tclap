
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


#ifndef __MULTIPLE_UNLABELED_ARGUMENT_HH__
#define __MULTIPLE_UNLABELED_ARGUMENT_HH__

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
  
	public:

		MultiArg( const string& desc,
				  Visitor* v = NULL);

		~MultiArg();

		bool processArg(int* i, int argc, char** argv); 

		const vector<T>& getValue() ;
};


template<class T>
MultiArg<T>::MultiArg(const string& desc, Visitor* v)
					                          
: Arg( "",    // flag
	  "...", // name 
	  desc,  // description
	  false, // required
	  true,
	  v)  // value required
{ };

template<class T>
MultiArg<T>::~MultiArg() { };

template<class T>
const vector<T>& MultiArg<T>::getValue() { return _values; };

template<class T>
bool MultiArg<T>::processArg(int *i, int argc, char** argv)
{
	// can be called multiple times
	T temp;
	string ss(argv[*i]);
	istringstream is(ss);
	is >> temp; 
	if ( is.fail() ) 
		throw( ArgException("Couldn't read argument value!", toString()));

	_values.push_back(temp);

	_checkWithVisitor();

	return true;
}

}

#endif
