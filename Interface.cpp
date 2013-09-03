/*
 * Interface.cpp
 *
 *  Created on: 2013-08-13
 *      Author: ar3roy
 */

#include "Interface.h"

string Interface::getName() {
	return this->name;
}

Interface::Interface(string name, InterfaceType type) {
	this->name = name;
	this->type = type;

}
void Interface::assignToSwitch(Switch* theSwitch)
{
	this->connectedToSwitch = theSwitch;
	this->connectedToSwitch->assignInterface(this);
}
Switch* Interface::getSwitch() {
	return this->connectedToSwitch;
}

InterfaceType Interface::getType()
{
	return this->type;
}

Interface::~Interface() {
	// TODO Auto-generated destructor stub
}

