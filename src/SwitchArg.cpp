
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

bool SwitchArg::combinedSwitchesMatch(string& combinedSwitches )
{
	// make sure this is actually a combined switch
	if ( combinedSwitches[0] != '-' )
		return false;

	// make sure it isn't a long name 
	if ( combinedSwitches[1] == '-' )
		return false;

	// ok, we're not specifying a ValueArg, so we know that we have
	// a combined switch list.  
	for ( int i = 1; i < combinedSwitches.length(); i++ )
		if ( combinedSwitches[i] == _flag[0] ) 
		{
			// update the combined switches so this one is no longer present
			// this is necessary so that no unlabeled args are matched
			// later in the processing.
			combinedSwitches.erase(i,1);
			return true;
		}

	// none of the switches passed in the list match. 
	return false;	
}


bool SwitchArg::processArg(int *i, vector<string>& args)
{
	if ( _ignoreable && Arg::ignoreRest() )
		return false;

	if ( argMatches( args[*i] ) || combinedSwitchesMatch( args[*i] ) )
	{
		// If we match on a combined switch, then we want to return false
		// so that other switches in the combination will also have a
		// chance to match.
		bool ret = false;
		if ( argMatches( args[*i] ) )
			ret = true;

		if ( _alreadySet )
			throw(ArgException("Argument already set!", toString()));	

		_alreadySet = true;

		if ( _value == true )
			_value = false;
		else
			_value = true;

		_checkWithVisitor();

		return ret;
	}
	else
		return false;
}

}
