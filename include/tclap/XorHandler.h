
/****************************************************************************** 
 * 
 *  file:  XorHandler.h
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

#ifndef __ORHANDLER_HH__
#define __ORHANDLER_HH__

#include <tclap/Arg.h>
#include <string>
#include <vector>

using namespace std;

namespace TCLAP {

class XorHandler
{
	protected:

		/**
		 * The list of of lists of Arg's to be or'd together.
		 */
		vector< vector<Arg*> > _orList;

	public:

		/**
		 * Constructor.  Does nothing.
		 */
		XorHandler( ); 

		/**
		 * Add a list of Arg*'s that will be orred together.
		 * \param ors - list of Arg* that will be xor'd.
		 */
		void add( vector<Arg*>& ors );
			
		/**
		 *
		 */
		int check( const Arg* a );

		/**
		 *
		 */
		void shortUsage();

		/**
		 *
		 */
		void longUsage();

		/**
		 *
		 */
		bool contains( const Arg* a );

};

}

#endif 
