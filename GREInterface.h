/*
 * GREInterface.h
 *
 *  Created on: 2013-08-28
 *      Author: ar3roy
 */

#ifndef GREINTERFACE_H_
#define GREINTERFACE_H_

#include "Interface.h"

class GRE_Interface: public Interface {

public:
	string remoteIP;
	GRE_Interface(string name);
	string getRemoteIP();
	virtual ~GRE_Interface();
};

#endif /* GREINTERFACE_H_ */
