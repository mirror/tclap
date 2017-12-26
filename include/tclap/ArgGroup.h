// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

/******************************************************************************
 *
 *  file:  ArgGroup.h
 *
 *  Copyright (c) 2017 Google LLC.
 *  All rights reserved.
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

#ifndef TCLAP_ARG_GROUP_H
#define TCLAP_ARG_GROUP_H

#include <list>

namespace TCLAP {

class ArgGroup {
public:
    typedef std::list<Arg*>::iterator iterator;
    typedef std::list<Arg*>::const_iterator const_iterator;

	explicit ArgGroup(bool required) : _required(required) {}

    iterator begin() { return _args.begin(); }
    iterator end() { return _args.end(); }
    const_iterator begin() const { return _args.begin(); }
    const_iterator end() const { return _args.end(); }

    ArgGroup& add(Arg &arg) {
	for(iterator it = begin(); it != end(); it++) {
	    if (arg == **it) {
		throw SpecificationException("Argument with same flag/name already exists!",
					     arg.longID());
	    }
	}

	_args.push_back(&arg);
	return *this;
    }

    bool validate(const std::vector<std::string>& args) {  // override
		Arg *arg = NULL;
		std::string flag;

		for (std::vector<std::string>::const_iterator it = args.begin();
			 it != args.end(); ++it) {
			Arg *candidate = find(*it);
			if (candidate != NULL) {  // Found match
				if (arg != NULL) {
					// We found a matching argument, but one was
					// already found previously.
					throw CmdLineParseException("Only one is allowed.",
												flag + " AND " + *it
												+ " provided.");
				}

				arg = candidate;
				flag = *it;
			}
		}

		return _required && !arg;
    }

	bool isRequired() const { return _required; }
	const std::string getName() const {
		std::ostringstream oss;
		std::string sep = "{";
		for (const_iterator it = begin(); it != end(); ++it) {
			oss << sep << (*it)->getName();
			sep = " | ";
		}

		oss << '}';
		return oss.str();
	}

protected:
    Arg* find(const std::string &s) const {
	for (const_iterator it = begin(); it != end(); ++it) {
	    if ((*it)->argMatches(s)) {
		return *it;
	    }
	}

	return NULL;
    }

	bool _required;
    std::list<Arg*> _args;
};

class EitherOf : public ArgGroup {
public:
	EitherOf() : ArgGroup(false) {}
};

class OneOf : public ArgGroup {
public:
	OneOf() : ArgGroup(true) {}
};

} //namespace TCLAP

#endif
