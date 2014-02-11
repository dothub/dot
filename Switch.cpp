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
 * Switch.cpp
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "Switch.h"
#include "Util.h"


Switch::Switch(unsigned long id, string name, string physicalMachineIP, string controllerIP,
        string controllerPort, SwitchType type, string dpid) {

    this->id = id;
    this->name = name;
    this->type = type;
    this->machine_ip = physicalMachineIP;
    this->controller_ip = controllerIP;
    this->controller_port = controllerPort;
    this->newVMAttachementID = 0;

    if(dpid.compare("") == 0)
        this->dpid = Util::intToHexString(id+1, dpid_width);

    else
        this->dpid = dpid;
}

void Switch::assignInterface(Interface* newInterface) {

    this->interfaceMap[newInterface->getName()]=newInterface;
}

string Switch::getDPID() {
    return this->dpid;
}

SwitchType Switch::getType() {
    return this->type;
}

string Switch::getIPOfMachine() {
    return this->machine_ip;
}


unsigned short Switch::getNewVMAttachementPoint() {
    return this->newVMAttachementID++;
}

unsigned long Switch::getID() {
    return this->id;
}

string Switch::getIPofController() {
    return this->controller_ip;
}
string Switch::getPortofController() {
    return this->controller_port;
}

string Switch::getName() {
    return this->name;
}

Switch::~Switch() {


}

