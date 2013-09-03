/*
 * Mapping.cpp
 *
 *  Created on: 2013-08-07
 *      Author: ar3roy
 */

#include "Mapping.h"
#include <iostream>

Mapping* Mapping::mapping = NULL;

Mapping* Mapping:: getMapping()
{
	if(mapping == NULL)
		mapping = new Mapping();

	return mapping;
}

Mapping::Mapping() {

}

string Mapping::getMachine(unsigned long switchID) {

	if(switchID < 0 || switchID >= this->switch2machine.size())
	{
		cout << "No switch found with the id: " << switchID << endl;
		return "None";
	}

	return this->switch2machine[switchID];
}

void Mapping::instertMapping(string machine) {

	this->switch2machine.push_back(machine);

}

Mapping::~Mapping() {

}

