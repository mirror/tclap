
/****************************************************************************** 
 * 
 *  file:  XorHandler.cpp
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


#include <tclap/XorHandler.h>

namespace TCLAP {

XorHandler::XorHandler( )
{ }

void XorHandler::add( vector<Arg*>& ors )
{ 
	_orList.push_back( ors );
}

void XorHandler::shortUsage()
{
	string out = "";
	for ( int i = 0; (unsigned int)i < _orList.size(); i++ )
	{
		out += " {";
		for ( ArgVectorIterator it = _orList[i].begin(); 
						it != _orList[i].end(); it++ )
			out += (*it)->shortID() + "|";

		out[out.length()-1] = '}';
	}

	cout << out;
}

void XorHandler::longUsage()
{
	for ( int i = 0; (unsigned int)i < _orList.size(); i++ )
	{
		for ( ArgVectorIterator it = _orList[i].begin(); 
			  it != _orList[i].end(); 
			  it++ )
		{
			cout << "   " << (*it)->longID() << endl
				 << "     " << (*it)->getDescription() << endl; 

			if ( it+1 != _orList[i].end() )
				cout << "       -- OR -- " << endl;
		}
		cout << endl << endl;
	}
}

int XorHandler::check( const Arg* a ) 
{
	// iterate over each XOR list
	for ( int i = 0; (unsigned int)i < _orList.size(); i++ )
	{
		// if the XOR list contains the arg..
		if ( find( _orList[i].begin(), _orList[i].end(), a ) != 
				   _orList[i].end() )
		{
			// go through and set each arg that is not a
			for ( ArgVectorIterator it = _orList[i].begin(); 
				  it != _orList[i].end(); 
				  it++ )	
				if ( a != (*it) )
					(*it)->xorSet();

			// return the number of required args that have now been set
			return (int)_orList[i].size();
		}
	}

	if ( a->isRequired() )
		return 1;
	else
		return 0;
}

bool XorHandler::contains( const Arg* a )
{
	for ( int i = 0; (unsigned int)i < _orList.size(); i++ )
		for ( ArgVectorIterator it = _orList[i].begin(); 
			  it != _orList[i].end(); 
			  it++ )	
			if ( a == (*it) )
				return true;

	return false;
}

}
