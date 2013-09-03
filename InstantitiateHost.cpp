/*
 * HostAttachment.cpp
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
 */

#include "InstantitiateHost.h"

InstantitiateHost::InstantitiateHost(Configurations* globalConf, Hosts* hosts, CommandExecutor* commandExec, InputTopology* topology, Mapping* mapping)
{
	this->globalConf = globalConf;
	this->hosts = hosts;
	this->commandExec = commandExec;
	this->topology = topology;
	this->mapping = mapping;
}

InstantitiateHost::~InstantitiateHost() {

}

