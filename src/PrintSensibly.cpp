
/****************************************************************************** 
 * 
 *  file:  PrintSensibly.cpp
 * 
 *  Copyright (c) 2004, Michael E. Smoot .
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


#include <tclap/PrintSensibly.h>

namespace TCLAP {


void spacePrint( ostream& os, 
				 const string& s, 
                 int maxWidth, 
	             int indentSpaces, 
	             int secondLineOffset )
{
	int len = (int)(s.length());

	if ( (len + indentSpaces > maxWidth) && maxWidth > 0 )
	{
		int allowedLen = maxWidth - indentSpaces;
		int start = 0;
		while ( start < len )
		{
			// find the substring length
			int stringLen = min( len - start, allowedLen );

			// trim the length so it doesn't end in middle of a word
			if ( stringLen == allowedLen )
				while ( s[stringLen+start] != ' ' && 
			   	        s[stringLen+start] != ',' &&
			   	        s[stringLen+start] != '|' )
					stringLen--;
			
			// check for newlines
			for ( int i = 0; i < stringLen; i++ )
				if ( s[start+i] == '\n' )
					stringLen = i+1;

			// print the indent	
			for ( int i = 0; i < indentSpaces; i++ )
				os << " ";

			if ( start == 0 )
			{
				// handle second line offsets
				indentSpaces += secondLineOffset;

				// adjust allowed len
				allowedLen -= secondLineOffset;
			}
			
			os << s.substr(start,stringLen) << endl;

			// so we don't start a line with a space
			if ( s[stringLen+start] == ' ' )
				start++;
			
			start += stringLen;
		}
	}
	else
	{
		for ( int i = 0; i < indentSpaces; i++ )
				os << " ";
		os << s << endl;
	}
}

}
