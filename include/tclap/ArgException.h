
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


#ifndef TCLAP_ARG_EXCEPTION_H
#define TCLAP_ARG_EXCEPTION_H

#include <string>
#include <exception>

namespace TCLAP {

/**
 * A simple class that defines and argument exception.  Should be caught
 * whenever a CmdLine is created and parsed.
 */
class ArgException : public std::exception
{
	public:
	
		/**
		 * Constructor.
		 * \param text - The text of the exception.
		 * \param id - The text identifying the argument source 
		 * of the exception.
		 */
		ArgException( const std::string& text = "undefined exception", 
					  const std::string& id = "undefined" )
			: std::exception(), _errorText(text), _argId( id ) { } 
		
		/**
		 * Destructor.
		 */
		virtual ~ArgException() throw() { }

		/**
		 * Returns the error text.
		 */
		std::string error() const { return ( _errorText ); }

		/**
		 * Returns the argument id.
		 */
		std::string argId() const  
		{ 
			if ( _argId == "undefined" )
				return " ";
			else
				return ( "Argument: " + _argId ); 
		}

		/**
		 * Returns the arg id and error text. 
		 */
		const char* what() throw() 
		{
			std::string ex = _argId + " -- " + _errorText;
			return ex.c_str();
		}

	private:

		/**
		 * The text of the exception message.
		 */
		std::string _errorText;

		/**
		 * The argument related to this exception.
		 */
		std::string _argId;

};

}

#endif

