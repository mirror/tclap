
/****************************************************************************** 
 * 
 *  file:  PrintSensibly.h
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

#ifndef __PRINTSENSIBLY_HH__
#define __PRINTSENSIBLY_HH__

#include <ostream>
#include <algorithm>
#include <string>

using namespace std;

namespace TCLAP {

/**
 * This function inserts line breaks and indents long strings according the 
 * params input. It will only break lines at spaces, commas and pipes.
 * \param os - The stream to be printed to.
 * \param s - The string to be printed.
 * \param maxWidth - The maxWidth allowed for the output line. 
 * \param indentSpaces - The number of spaces to indent the first line. 
 * \param secondLineOffset - The number of spaces to indent the second
 * and all subsequent lines in addition to indentSpaces.
 */
void spacePrint( ostream& os, 
				 const string& s, 
				 int maxWidth, 
				 int indentSpaces=0, 
				 int secondLineOffset=0 );

}

#endif
