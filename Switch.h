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
 *      Author: ar3roy
 */

#ifndef SWITCH_H_
#define SWITCH_H_
#include <string>
#include <map>
#include "Interface.h"
class Interface;

using namespace std;

enum SwitchType { TOPO_SWITCH, GATEWAY_SWITCH };

class Switch {

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
	void assignInterface(Interface* newInterface);
	string getDPID();
	unsigned long getID();
	unsigned short getNewVMAttachementPoint();
	SwitchType getType();
	string getName();
	string getIPOfMachine();
	string getIPofController();
	string getPortofController();
	virtual ~Switch();
};

#endif /* SWITCH_H_ */
