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
 * Switch2Controller.h
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef SWITCH2CONTROLLER_H_
#define SWITCH2CONTROLLER_H_
#include "Controllers.h"
#include <map>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;

/**
* This is a singleton class for storing switch2controller assignment.
*/
class Switch2Controller {

    LoggerPtr* selfLogger;
    Switch2Controller(Controllers* controllers);

    static Switch2Controller* switch2Controller;

    Controllers * controllers;
    map<unsigned long, unsigned int> sw2controllerMap;

public:
    
    static Switch2Controller* getSwitch2Controller(Controllers* controllers);
   
    /**
    * The function to return the ID of the controller of the switch 
    * @param - switchId - ID of the switch 
    * @return - ID as an integer
    */
    unsigned int getControllerId(unsigned long switchId);
    
    /**
    * The function to return the IP address of the controller of the switch 
    * @param - switchId - ID of the switch 
    * @return - IP address as a string
    */
    string getControllerIP(unsigned long switchId);
    
    /**
    * The function to return the port of the controller of the switch 
    * @param - switchId - ID of the switch 
    * @return - Port as a string
    */
    string getControllerPort(unsigned long switchId);
    /**
    * The function to populate switch 2 controller from a file.
    * @param fileName - Name of the file
    */
    void loadConfiguration(string fileName);
    
    /**
    * Destructor of the class.
    */
    virtual ~Switch2Controller();
};

#endif /* SWITCH2CONTROLLER_H_ */
