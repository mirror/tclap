
/****************************************************************************** 
 * 
 *  file:  HelpVisitor.h
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

#ifndef TCLAP_HELP_VISITOR_H
#define TCLAP_HELP_VISITOR_H

#include <tclap/Visitor.h>

namespace TCLAP {

/**
 * A Visitor object that calls the usage method of a given CmdLine.
 */
class HelpVisitor: public Visitor
{
	protected:

		/**
		 * The CmdLine that will be called for the usage method.
		 */
		CmdLine* _cmd;

	public:

		/**
		 * Constructor.
		 * \param cmd - The CmdLine that will called for usage method.
		 */
		HelpVisitor(CmdLine* cmd) : Visitor(), _cmd( cmd ) { }

		/**
		 * Calls the usage method of the CmdLine.
		 */
		void visit() { _cmd->usage(0); }
		
};

}

#endif
