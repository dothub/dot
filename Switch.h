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
 * Switch.h
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef SWITCH_H_
#define SWITCH_H_
#include <string>
#include <map>
#include "Interface.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

class Interface;

using namespace std;

enum SwitchType { TOPO_SWITCH, GATEWAY_SWITCH };

/**
* This is the class for keeping infromation of the switch in the DOT topology.
*/
class Switch {
    LoggerPtr* selfLogger;
    const static unsigned int dpid_width = 16;

protected:
    unsigned long id;
    string dpid;
    string name;

    SwitchType type;
    string machine_ip;
    string controller_ip;
    string controller_port;
    unsigned short newVMAttachementID;
    map<string, Interface* >  interfaceMap;

public:

    Switch(unsigned long id, string name, string physicalMachineIP, string controllerIP="", string controllerPort="",
            SwitchType type=TOPO_SWITCH, string dpid="");
    
    /**
    * The function assigns an interface to the switch
    * @param- newInterface- Pointer to the interface
    */

    void assignInterface(Interface* newInterface);
    
    /**
    * The function to return the datapath id of a switch
    * @return - dpid of the switch
    */

    string getDPID();
    /**
    * The function to return the id of a switch
    * @return - id of the switch
    */
    unsigned long getID();
    
    /**
    * The function to return the number of vnet interface
    * @return - id of the vnet interface
    */
    unsigned short getNewVMAttachementPoint();
    /**
    * The function to return the type of a switch
    * @return - Type of the switch
    */
    SwitchType getType();
    
    /**
    * The function to return the name of a switch
    * @return - Name of the switch
    */
    string getName();
    
    /**
    * The function to return the IP address of the machine where the switch is provisioned
    * @return - IP address as a string
    */
    string getIPOfMachine();
    /**
    * The function to return the IP address of the controller of the switch 
    * @return - IP address as a string
    */

    string getIPofController();
    /**
    * The function to return the port  of the controller of the switch 
    * @return - Port as a string
    */
    string getPortofController();
    
    /**
    * Destructor of the class.
    */
    virtual ~Switch();
};

#endif /* SWITCH_H_ */
