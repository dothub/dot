/*
 * OVS_1_9.h
 *
 *  Created on: 2013-08-28
 *      Author: ar3roy
 */

#ifndef OVS_1_9_H_
#define OVS_1_9_H_

#include "InstantitiateSwitch.h"

class OVS_1_9: public InstantitiateSwitch {
protected:
	string createClearAllRules(Switch* newSwitch);
	string createStaticTunnelRule(Switch* newSwitch, unsigned int tunnel_id, unsigned int input_port, unsigned int output_port);
public:
	OVS_1_9(CommandExecutor* commandExec);
	virtual ~OVS_1_9();
	void clearSwitch(Switch* newSwitch);
	void runSwitch(Switch* newSwitch);
	void attachPort(Switch* newSwitch, Interface* newInterface);
	void assignPortNumber(Switch* newSwitch, Interface* newInterface);
	void assignStaticTunnelRule(Switch* newSwitch, list<pair<unsigned int, pair<unsigned int, unsigned int> > > rules );
	void clearAllRules(Switch* newSwitch);

};

#endif /* OVS_1_9_H_ */
