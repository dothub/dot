/*
 * Switch.cpp
 *
 *  Created on: 2013-08-13
 *      Author: ar3roy
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

