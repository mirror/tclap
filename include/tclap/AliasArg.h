// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

/******************************************************************************
 *
 *  file:  AliasArg.h
 *
 *  Copyright (c) 2018 Google LLC
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

#ifndef TCLAP_ALIAS_ARG_H
#define TCLAP_ALIAS_ARG_H

#include <tclap/Arg.h>

namespace TCLAP {

// Prototype implementation for
// https://sourceforge.net/p/tclap/feature-requests/5/
//
// Probably would require to introduce a "TypedArg" interface and
// implement it in ValueArg, MultiArg, etc to provide a getTypeDesc().
// Alternatively have a "format{Short,Long}ID" function that takes the
// flag/name as argument in Arg. Otherwise there is no way to get a
// reasonable looking documentation string. Still, it is not clear how
// to present it in the best way.
class AliasArg : public Arg {
public:
    /**
     * Create an argument alias.
     *
     * @param flag The one character flag that identifies this
     * argument on the command line.
     *
     * @param name A one word name for the argument. Can be used as a
     * long flag on the command line.
     *
     * @param alias The argument that will be aliased by this command.
     */
    AliasArg(const std::string &flag, const std::string &name, Arg &alias)
        : Arg(flag, name, getDescription(alias.getName()), alias.isRequired(),
              alias.isValueRequired(), 0), _alias(alias) {}


    AliasArg(const std::string &flag, const std::string &name, Arg &alias,
             CmdLineInterface &parser)
        : Arg(flag, name, getDescription(alias.getName()), alias.isRequired(),
          alias.isValueRequired(), 0), _alias(alias) {
        parser.add(this);
    }

    bool processArg(int *i, std::vector<std::string> &args)  // override
    {
        return _alias.processArg(i, args);
    }

    std::string shortID(const std::string &) const  // override
    {
        std::string id = "";

        if ( _flag != "" )
            id = Arg::flagStartString() + _flag;
        else
            id = Arg::nameStartString() + _name;

        id += " alias for " + Arg::flagStartString() + _alias.getFlag();
        if ( !_required )
            id = "[" + id + "]";

        return id;
    }

    std::string longID(const std::string &) const  // override
    {
        std::string id = "";

        if ( _flag != "" ) {
            id += Arg::flagStartString() + _flag + ", ";
        }

        id += Arg::nameStartString() + _name;

        return id;
    }

    std::string getDescription(const std::string &name) const
    {
        return "Alias for " + Arg::nameStartString() + name;
    }

    void reset()  // override
    {
        _alias.reset();
    }

private:
    /**
     * Prevent accidental copying
     */
    AliasArg(const AliasArg &rhs);
    AliasArg &operator=(const AliasArg &rhs);

    Arg &_alias;
};

}  // namespace TCLAP

#endif
