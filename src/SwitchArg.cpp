
/****************************************************************************** 
 * 
 *  file:  SwitchArg.cpp
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


#include <tclap/SwitchArg.h>

namespace TCLAP {

SwitchArg::SwitchArg(const string& flag, 
	 		         const string& name, 
     		   		 const string& desc, 
	     	    	 bool _default,
					 Visitor* v )
: Arg(flag, name, desc, false, false, v),
  _value( _default )
{ 
	if ( _flag == "" )
		throw(ArgException("Cannot have an unlabeled SwitchArg!",toString()));
};

SwitchArg::~SwitchArg() { };

bool SwitchArg::getValue() { return _value; };

bool SwitchArg::processArg(int *i, int argc, char** argv)
{
	if ( argMatches( argv[*i] ) )
	{
		if ( _alreadySet )
			throw(ArgException("Argument already set!", toString()));	

		_alreadySet = true;

		if ( _value == true )
			_value = false;
		else
			_value = true;

		_checkWithVisitor();

		return true;
	}
	else
		return false;
}

}
