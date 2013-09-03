/*
 * Switch2Controller.cpp
 *
 *  Created on: 2013-08-13
 *      Author: ar3roy
 */

#include "Switch2Controller.h"
#include <stddef.h>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

Switch2Controller* Switch2Controller::switch2Controller = NULL;

Switch2Controller* Switch2Controller:: getSwitch2Controller(Controllers* controllers)
{
	if(switch2Controller == NULL)
		switch2Controller = new Switch2Controller(controllers);

	return switch2Controller;
}

Switch2Controller::Switch2Controller(Controllers* controllers) {

	this->controllers = controllers;

}

void Switch2Controller::loadConfiguration(string fileName) {

	ifstream fin(fileName.c_str());

	if(fin.is_open())
	{
		unsigned long numberOfSwitches;
		fin >> numberOfSwitches;


		for(unsigned int i = 0; i < numberOfSwitches; i++)
		{
			string switch_str, controller;
			fin >> switch_str >> controller;

			this->sw2controllerMap[atol(switch_str.substr(1).c_str())-1] = atoi(controller.substr(1).c_str())-1;
		}


		fin.close();
	}
	else
		cout << "Unable to open switch to controller file: " << fileName << endl;
}

unsigned int Switch2Controller::getControllerId(unsigned long switchId) {

	return this->sw2controllerMap[switchId];
}

string Switch2Controller::getControllerIP(unsigned long switchId) {

	return this->controllers->getIPAddress(this->sw2controllerMap[switchId]);
}

string Switch2Controller::getControllerPort(unsigned long switchId) {

	return this->controllers->getPort(this->sw2controllerMap[switchId]);
}

Switch2Controller::~Switch2Controller() {

}

