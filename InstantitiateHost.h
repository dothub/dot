/*
 * HostAttachment.h
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
 */

#ifndef INSTANTITIATEHOST_H
#define INSTANTITIATEHOST_H
#include <string>
#include "Hosts.h"
#include "Configurations.h"
#include "CommandExecutor.h"
#include "InputTopology.h"
#include "Mapping.h"

using namespace std;
INSTANTITIATEHOST_H
class InstantitiateHost {

protected:
	Configurations* globalConf;
	Hosts* hosts;
	CommandExecutor* commandExec;
	Mapping* mapping;
	InputTopology* topology;

	virtual void createHost2SwitchAttachmentConf()=0;
	virtual void loadConfiguration(string fileName)=0;

public:
	InstantitiateHost(Configurations* globalConf, Hosts* hosts, CommandExecutor* commandExec, 	InputTopology * topology, Mapping* mapping);

	virtual void prepare()=0;
	virtual void startHost(unsigned long host_id)=0;
	virtual string tapInterfacePrefix()=0;

	virtual ~InstantitiateHost();
};

#endif /* INSTANTITIATEHOST_H */
