/*
 * Interface.h
 *
 *  Created on: 2013-08-13
 *      Author: ar3roy
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "Link.h"
#include "Switch.h"
#include <string>
using namespace std;


class Switch;
class Link;

enum InterfaceType { TAP, VETH, GRE };

class Interface {

protected:
	string name;
	Switch * connectedToSwitch;
	InterfaceType type;

public:
	unsigned int port;
	Link* belongsToLink;
	Interface(string name, InterfaceType type);
	void assignToSwitch(Switch* theSwitch);
	Switch * getSwitch();
	string getName();
	InterfaceType getType();
	virtual ~Interface();
};

#endif /* INTERFACE_H_ */
