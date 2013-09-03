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
