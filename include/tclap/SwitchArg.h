
/****************************************************************************** 
 * 
 *  file:  SwitchArg.h
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


#ifndef __SWITCH_ARG_HH__
#define __SWITCH_ARG_HH__

#include <string>
#include <vector>
#include <sstream>
#include <tclap/Arg.h>
#include <tclap/ArgException.h>

using namespace std;

namespace TCLAP {

class SwitchArg : public Arg
{
	protected:

		bool _value;
  
	public:

		SwitchArg(const string& flag, 
			      const string& name, 
			      const string& desc,
			      bool _default,
				  Visitor* v = NULL);

		~SwitchArg();

		bool processArg(int* i, int argc, char** argv); 

		bool getValue() ;
};

}

#endif
