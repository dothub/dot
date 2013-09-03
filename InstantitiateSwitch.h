/*
 * InstantitiateSwitch.h
 *
 *  Created on: 2013-08-28
 *      Author: ar3roy
 */

#ifndef INSTANTITIATESWITCH_H_
#define INSTANTITIATESWITCH_H_
#include <string>
#include <list>
#include "Switch.h"
#include "CommandExecutor.h"
#include "Interface.h"

using namespace std;

class InstantitiateSwitch {
protected:
	CommandExecutor* commandExec;
	virtual string createClearAllRules(Switch* newSwitch)=0;

public:
	InstantitiateSwitch(CommandExecutor* commandExec);
	virtual void clearSwitch(Switch* newSwitch)=0;
	virtual void runSwitch(Switch* newSwitch)=0;
	virtual void attachPort(Switch* newSwitch, Interface* newInterface)=0;
	virtual void assignPortNumber(Switch* newSwitch, Interface* newInterface)=0;
	virtual string createStaticTunnelRule(Switch* newSwitch, unsigned int tunnel_id, unsigned int input_port, unsigned int output_port)=0;
	virtual void assignStaticTunnelRule(Switch* newSwitch, list<pair<unsigned int, pair<unsigned int, unsigned int> > > rules )=0;
	virtual void clearAllRules(Switch* newSwitch)=0;

	virtual ~InstantitiateSwitch();
};

#endif /* INSTANTITIATESWITCH_H_ */
