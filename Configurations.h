/*
 * Configurations.h
 *
 *  Created on: 2013-08-06
 *      Author: ar3roy
 */

#ifndef CONFIGURATIONS_H_
#define CONFIGURATIONS_H_

#include <string>

using namespace std;

class Configurations {

	static Configurations* configuration;
	Configurations(string configurationFileName);
	void loadConfiguration();
	string globalConfigurationFile;

public:
	string masterName;
	string masterIPAddress;
	string hostImage;
	string logicalTopologyFile;
	string physicalTopologyFile;
	string controllerInfoFile;
	string hostInfoFile;
	string switch2ControllerFile;
	string partitioningAlgorithm;
	string partitioningAlgoConfFile;
	string credentialFile;
	string hypervisor;
	string hypervisorConfigurationFile;
	bool delayBetweenPhysicalMachine;
	string physicalMachineDelayFile;

	static Configurations* getConfiguration(string configurationFileName);

	virtual ~Configurations();
};

#endif /* CONFIGURATIONS_H_ */
