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

#include <tclap/Arg.h>
#include <tclap/ArgContainer.h>
#include <tclap/CmdLineInterface.h>

#include <list>

namespace TCLAP {

/**
 * ArgGroup is the base class for implementing groups of arguments
 * that are mutually exclusive (it replaces the deprecated xor
 * handler). It is not expected to be used directly, rather one of the
 * EitherOf or OneOf derived classes are used.
 */
class ArgGroup : public ArgContainer {
public:
    typedef std::list<Arg*> Container;
    typedef Container::iterator iterator;
    typedef Container::const_iterator const_iterator;

    virtual ~ArgGroup() {}

    /// Add an argument to this arg group
    ArgContainer &add(Arg &arg) { return add(&arg); }

    /// Add an argument to this arg group
    ArgContainer &add(Arg *arg);

	/**
	 * Validates that args match the constraints of the ArgGroup.
	 *
     * @internal
	 * Throws an CmdLineParseException if there is an issue (except
	 * missing required argument, in which case true is returned).
	 *
	 * @retval true iff a required argument was missing.
	 */
    virtual bool validate(const std::vector<std::string>& args) = 0;

	/**
     * Returns true if this argument group is required
     *
     * @internal
     */
	virtual bool isRequired() const = 0;

    /**
     * Returns true if this argument group is exclusive.
     *
     * @internal
     * Being exclusive means there is a constraint so that some
     * arguments cannot be selected at the same time.
     */
    virtual bool isExclusive() const = 0;

    /**
     * Used by the parser to connect itself to this arg group.
     *
     * @internal
     * This is needed so that existing and subsequently added args (in
     * this arg group) are also added to the parser (and checked for
     * consistency with other args).
     */
    void setParser(CmdLineInterface &parser) {
        if (_parser) {
            throw SpecificationException("Arg group can have only one parser");
        }

        _parser = &parser;
        for (iterator it = begin(); it != end(); ++it) {
            parser.add(*it);
        }
    }

	/// Returns the argument group's name.
	const std::string getName() const;

	iterator begin() { return _args.begin(); }
    iterator end() { return _args.end(); }
    const_iterator begin() const { return _args.begin(); }
    const_iterator end() const { return _args.end(); }

protected:
	// No direct instantiation
	ArgGroup() : _parser(0), _args() {}

	// Lookup arg that matches s, if any
    Arg* find(const std::string &s) const {
		for (const_iterator it = begin(); it != end(); ++it) {
			if ((*it)->argMatches(s)) {
				return *it;
			}
		}

		return NULL;
    }

private:
    explicit ArgGroup(const ArgGroup&);
    ArgGroup& operator=(const ArgGroup&);  // no copy

    CmdLineInterface *_parser;
    Container _args;
};


/**
 * Implements common functionality for exclusive argument groups.
 *
 * @internal
 */
class ExclusiveArgGroup : public ArgGroup {
public:
    bool validate(const std::vector<std::string>& args);
    bool isExclusive() const { return true; }

protected:
    ExclusiveArgGroup() {}
    explicit ExclusiveArgGroup(CmdLineInterface &parser) {
        parser.add(*this);
    }
};

/**
 * Implements a group of arguments where at most one can be selected.
 */
class EitherOf : public ExclusiveArgGroup {
public:
	EitherOf() {}
    explicit EitherOf(CmdLineInterface &parser) : ExclusiveArgGroup(parser) {}

    bool isRequired() const { return false; }
};

/**
 * Implements a group of arguments where exactly one must be
 * selected. This corresponds to the deprecated "xoradd".
 */
class OneOf : public ExclusiveArgGroup {
public:
	OneOf() {}
    explicit OneOf(CmdLineInterface &parser) : ExclusiveArgGroup(parser) {}

    bool isRequired() const { return true; }
};

inline ArgContainer &ArgGroup::add(Arg *arg) {
	for(iterator it = begin(); it != end(); it++) {
	    if (*arg == **it) {
			throw SpecificationException("Argument with same flag/name already exists!",
										 arg->longID());
	    }
	}

	_args.push_back(arg);
    if (_parser) {
        _parser->add(arg);
    }

	return *this;
}

inline bool ExclusiveArgGroup::validate(const std::vector<std::string>& args) {
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

	return isRequired() && !arg;
}

inline const std::string ArgGroup::getName() const {
	std::string name;
	std::string sep = "{";  // TODO: this should change for
                            // non-exclusive arg groups
	for (const_iterator it = begin(); it != end(); ++it) {
		name += sep + (*it)->getName();
		sep = " | ";
	}

	return name + '}';
}

} //namespace TCLAP

#endif
