/*
 * GREInterface.cpp
 *
 *  Created on: 2013-08-28
 *      Author: ar3roy
 */

#include "GREInterface.h"

GRE_Interface::GRE_Interface(string name)
	:Interface(name, GRE)
{

}

string GRE_Interface::getRemoteIP() {
	return this->remoteIP;
}

GRE_Interface::~GRE_Interface() {

}

