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
