
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

bool Arg::_ignoreRest = false;

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
  _ignoreable(true),
  _visitor( v )
{ 
	if ( _flag.length() > 1 ) 
		throw(ArgException("Argument flag can only be one character long",
							toString() ) );
};

Arg::Arg()
: _name(""),
  _description(""),
  _flag(""),
  _required(false),
  _valueRequired(false),
  _alreadySet(false)
{ };

Arg::Arg(const Arg& a)
: _name(a._name),
  _description(a._description),
  _flag(a._flag),
  _required(a._required),
  _valueRequired(a._valueRequired),
  _alreadySet(a._alreadySet)
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
	} 
	return *this;
};

string Arg::shortID( const string& valueId ) const
{
	string id = "";

	id = "-" + _flag;
	
	if ( _valueRequired )
		id += " <" + valueId  + ">";

	if ( !_required )
		id = "[" + id + "]";

	return id;
}

string Arg::longID( const string& valueId ) const
{
	string id = "";

	id = "-" + _flag;

	if ( _valueRequired )
		id += " <" + valueId + ">";


	id += ",  --" + _name;

	if ( _valueRequired )
		id += " <" + valueId + ">";
			
	return id;

}

bool Arg::operator==(const Arg& a)
{
	if ( _flag == a._flag || 
		 _name == a._name || 
		 _description == a._description )
		return true;
	else
		return false;
}

// should be overridden
bool Arg::processArg(int* i, vector<string>& args )
{
	cerr << "WARNING:   Ignoring unknown argument: " << args[*i] << endl;	
	return false;
}

const string& Arg::getName() const { return _name; } ;

string Arg::getDescription() const 
{
	string desc = "";
	if ( _required )
		desc = "(required)  ";

	if ( _valueRequired )
		desc += "(value required)  ";

	desc += _description;
	return desc; 
};

const string& Arg::getFlag() const { return _flag; };
bool Arg::isRequired() const { return _required; }
bool Arg::isValueRequired() const { return _valueRequired; }
bool Arg::isAlreadySet() const { return _alreadySet; }
bool Arg::isIgnoreable() const { return _ignoreable; }

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
