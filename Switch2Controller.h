/*
 * Switch2Controller.h
 *
 *  Created on: 2013-08-13
 *      Author: ar3roy
 */

#ifndef SWITCH2CONTROLLER_H_
#define SWITCH2CONTROLLER_H_
#include "Controllers.h"
#include <map>
using namespace std;

class Switch2Controller {
	Switch2Controller(Controllers* controllers);

	static Switch2Controller* switch2Controller;

	Controllers * controllers;
	map<unsigned long, unsigned int> sw2controllerMap;

public:
	static Switch2Controller* getSwitch2Controller(Controllers* controllers);
	unsigned int getControllerId(unsigned long switchId);
	string getControllerIP(unsigned long switchId);
	string getControllerPort(unsigned long switchId);
	void loadConfiguration(string fileName);
	virtual ~Switch2Controller();
};

#endif /* SWITCH2CONTROLLER_H_ */
