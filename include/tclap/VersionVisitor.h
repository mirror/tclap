
/****************************************************************************** 
 * 
 *  file:  VersionVisitor.h
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


#ifndef __VERSION_VISITOR_H__
#define __VERSION_VISITOR_H__

#include <tclap/Visitor.h>

namespace TCLAP {

/**
 * A Vistor that will call the version method of the given CmdLine and
 * then exit.
 */
class VersionVisitor: public Visitor
{
	protected:

		/**
		 * The CmdLine of interest.
		 */
		CmdLine* _cmd;
		
	public:

		/**
		 * Constructor.
		 * \param cmd - The CmdLine whose version method will be called.
		 */
		VersionVisitor(CmdLine* cmd) : Visitor(), _cmd( cmd ) { }

		/**
		 * Prints the version to stdout.
		 */
		void visit() { _cmd->version(0); }
};

}

#endif
