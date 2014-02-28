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
 * VLink.h
 *
 *  Created on: 2013-08-28
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef VLINK_H_
#define VLINK_H_

#include "AbstractLink.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;


/**
* This is the class to create a linux virtual ethernet link.
*/
class VLink: public AbstractLink {
    /**
    * The event logger of this class.
    */
    LoggerPtr* selfLogger;

public:
    /**
    * Constructor of the class.
    * @param commandExec - Pointer to the global object of CommandExecutor.
    */
    VLink(CommandExecutor* commandExec);
   
    /**
    * Destructor of the class.
    */
    virtual ~VLink();
   /**
    * Destructor of AbstractLink class.
    */
    void createLink(Link* newLink);
};

#endif /* VLINK_H_ */
