
/****************************************************************************** 
 * 
 *  file:  CmdLine.h
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

#ifndef __CMDLINE_HH__
#define __CMDLINE_HH__

#include <tclap/Arg.h>
#include <tclap/SwitchArg.h>
#include <tclap/MultiArg.h>
#include <tclap/UnlabeledMultiArg.h>
#include <tclap/ValueArg.h>
#include <tclap/UnlabeledValueArg.h>
#include <tclap/Visitor.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <iomanip>
#include <algorithm>

using namespace std;

namespace TCLAP {

class CmdLine
{
	protected:
		list<Arg*> _argList;
		string _progName;
		string _message;
		string _version;
		int _maxLength;
		int _numRequired;

	public:
		CmdLine(char* progName, 
				const string& message, 
				const string& version = "none" );

		void add( Arg& a );
		void usage( int exitVal = 0 );
		void version( int exitVal = 0 );
		void parse(int argc, char** argv);
};

}

// These have to be included _after_ CmdLine is declared, because
// they rely on CmdLine existing.  Don't know why I can't forward
// declare CmdLine...   this works.

#include "HelpVisitor.h"
#include "VersionVisitor.h"
#include "IgnoreRestVisitor.h"


#endif 
