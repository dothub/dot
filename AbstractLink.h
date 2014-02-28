/*
* This file is part of DOT.
*
*     DOT is free software: you can redistribute it and/or modify
*     it under the terms of the GNU General Public License as published by
*     the Free Software Foundation, either version 3 of the License, or
*     (at your option) any later version.
*
*     DOT is distributed in the hope that it will be useful,
*     but WITHOUT ANY WARRANTY; without even the implied warranty of
*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*     GNU General Public License for more details.
*
*     You should have received a copy of the GNU General Public License
*     along with DOT.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright 2011-2013 dothub.org
*/

/*
 * AbstractLink.h
 *
 *  Created on: 2013-08-28
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef ABSTRACTLINK_H_
#define ABSTRACTLINK_H_
#include "CommandExecutor.h"
#include "Link.h"
#include "Global.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**
* This is the base class for provisioning virtual link for different environment.
*/
class AbstractLink {
    /**
    * The event logger of this class.
    */
    LoggerPtr* selfLogger;
protected:
    /**
    * Pointer to the CommandExecutor Object.
    */   
    CommandExecutor* commandExec;
public:
    /**
    * Constructor of AbstractLink class.
    * @param commandExec - Pointer to the global object of CommandExecutor.
    */ 
    AbstractLink(CommandExecutor* commandExec);
    /**
    * Destructor of AbstractLink class.
    */
    virtual ~AbstractLink();
   
    /**
    * This function provides a an interface to create a vlink from a link attribute
    * @param newLink - The object containing the link properties.
    */
    void virtual createLink(Link* newLink)=0;
};

#endif /* ABSTRACTLINK_H_ */
