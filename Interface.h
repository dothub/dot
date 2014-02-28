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
 * Interface.h
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "Link.h"
#include "Switch.h"
#include <string>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;


class Switch;
class Link;

enum InterfaceType { TAP, VETH, GRE };

/**
* This class stores the information about provisioned Interface.
*/

class Interface {

    LoggerPtr* selfLogger;
protected:

    string name;
    Switch * connectedToSwitch;
    InterfaceType type;

public:
    unsigned int port;
    Link* belongsToLink;
  
    /**
    * Constructor of the class.
    * @param name - Interface Name 
    * @param - type - Type of the interface
    */ 
    Interface(string name, InterfaceType type);
    
     /**
     * This function keeps the switch of the interface.
    * @param theSwitch - Pointer to the switch where the interface belongs
    */

    void assignToSwitch(Switch* theSwitch);
    
    /**
     * This function returns the switch of the interface.
    * @return Pointer to the switch where the interface belongs
    */
    Switch * getSwitch();
    /**
     * This function returns the name  of the interface.
    */

    string getName();
    /**
     * This function returns the type of the interface.
    */
    InterfaceType getType();
    
    /**
    * Destructor of the class.
    */

    virtual ~Interface();
};

#endif /* INTERFACE_H_ */
