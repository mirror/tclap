
/****************************************************************************** 
 * 
 *  file:  Arg.cpp
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


#include <tclap/Arg.h>

namespace TCLAP {

Arg::Arg( const string& flag, 
		 const string& name, 
		 const string& desc, 
		 bool req,
		 bool valreq,
		 Visitor* v)
: _name(name),
  _description(desc),
  _flag(flag),
  _required(req),
  _valueRequired(valreq),
  _alreadySet(false),
  _visitor( v )
{ 
	if ( _flag == "" )
		_labeled = false;
	else
		_labeled = true;
};

Arg::Arg()
: _name(""),
  _description(""),
  _flag(""),
  _required(false),
  _valueRequired(false),
  _alreadySet(false),
  _labeled(false)
{ };

Arg::Arg(const Arg& a)
: _name(a._name),
  _description(a._description),
  _flag(a._flag),
  _required(a._required),
  _valueRequired(a._valueRequired),
  _alreadySet(a._alreadySet),
  _labeled(a._labeled)
{ };

Arg::~Arg() { };

Arg& Arg::operator=(const Arg& a)
{
	if ( this != &a )
	{
		_name = a._name;
		_description = a._description;
		_flag = a._flag;
		_required = a._required;
		_valueRequired = a._valueRequired;
		_alreadySet = a._alreadySet;
		_labeled = a._labeled;
	} 
	return *this;
};

/*
bool Arg::operator<(const Arg& a) const
{
	if ( _required && !a._required )
		return false;

	if ( !_required && a._required )
		return true;

	if ( _labeled && !a._labeled )
		return false;

	if ( !_labeled && a._labeled )
		return true;

	return false;
}
*/

bool Arg::operator==(const Arg& a)
{
	if ( _labeled )
	{
		if ( _flag == a._flag || _name == a._name )
			return true;
		else
			return false;
	}
	else
	{
		if ( _name == a._name || _description == a._description )
			return true;
		else
			return false;
	}
}

// should be overridden
bool Arg::processArg(int* i, int argc, char** argv)
{
	cerr << "WARNING:   Ignoring unknown argument: " << argv[*i] << endl;	
	return false;
}

const string& Arg::getName() const { return _name; } ;
const string& Arg::getDescription() const { return _description; };
const string& Arg::getFlag() const { return _flag; };
bool Arg::isRequired() const { return _required; }
bool Arg::isValueRequired() const { return _valueRequired; }
bool Arg::isAlreadySet() const { return _alreadySet; }
bool Arg::isLabeled() const { return _labeled; }

bool Arg::argMatches( const string& argFlag ) const
{
	if ( argFlag == "-" + _flag ||
		 argFlag == "--" + _name )
		return true;
	else
		return false;
}

string Arg::toString() const
{
	string s = "-" + _flag + " (--" + _name + ")";
	return s;
}

void Arg::_checkWithVisitor() const
{
	if ( _visitor != NULL )
		_visitor->visit();
}

}
