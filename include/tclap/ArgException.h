
/****************************************************************************** 
 * 
 *  file:  ArgException.h
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


#ifndef __ARG_EXCEPTION_H__
#define __ARG_EXCEPTION_H__

#include <string>

using namespace std;

namespace TCLAP {

class ArgException
{
	public:
		
		ArgException( const string& text = "undefined exception", 
					  const string& id = "undefined" )
			: _errorText(text), _argId( id ) {}; 
		
		ArgException(const ArgException& e) 
			: _errorText(e._errorText), _argId(e._argId) {};

		~ArgException(){};

	
		ArgException& operator=( const ArgException& e )
		{ 
			if ( this != &e ) 
			{
				_errorText = e._errorText;  
				_argId = e._argId;
			}
			return *this; 
		};

		string error() { return ( _errorText ); };
		string argId() { return ( _argId ); };

	private:

		string _errorText;
		string _argId;

};

}

#endif

