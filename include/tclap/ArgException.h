
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

/**
 * A simple class that defines and argument exception.  Should be caught
 * whenever a CmdLine is created and parsed.
 */
class ArgException
{
	public:
	
		/**
		 * Constructor.
		 * \param text - The text of the exception.
		 * \param id - The text identifying the argument source 
		 * of the exception.
		 */
		ArgException( const string& text = "undefined exception", 
					  const string& id = "undefined" )
			: _errorText(text), _argId( id ) {}; 
		
		/**
		 * Copy constructor.
		 * \param e - The ArgException that will be copied.
		 */
		ArgException(const ArgException& e) 
			: _errorText(e._errorText), _argId(e._argId) {};

		/**
		 * Destructor.
		 */
		~ArgException() {};

	
		/**
		 * Assignment operator.
		 * \param e - The ArgException that will be assigned
		 * to this.
		 */
		ArgException& operator=( const ArgException& e )
		{ 
			if ( this != &e ) 
			{
				_errorText = e._errorText;  
				_argId = e._argId;
			}
			return *this; 
		};

		/**
		 * Returns the error text.
		 */
		string error() { return ( _errorText ); };

		/**
		 * Returns the argument id.
		 */
		string argId() 
		{ 
			if ( _argId == "undefined" )
				return " ";
			else
				return ( "Argument: " + _argId ); 
		};

	private:

		/**
		 * The text of the exception message.
		 */
		string _errorText;

		/**
		 * The argument related to this exception.
		 */
		string _argId;

};

}

#endif

