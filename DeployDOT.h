/*
 * DeployDOT.h
 *
 *  Created on: 2013-08-28
 *      Author: ar3roy
 */

#ifndef DEPLOYDOT_H_
#define DEPLOYDOT_H_
#include "DOTTopology.h"
#include "InstantitiateSwitch.h"
#include "InstantitiateLink.h"
#include "InstantitiateHost.h"

class DOT_Topology;

class DeployDOT {

	DOT_Topology* dotTopology;
	InstantitiateSwitch*  instantitiatedSwitch;
	InstantitiateLink* instantitiatedLink;
	InstantitiateHost* instantitiatedHost;
	CommandExecutor* commandExecutor;

public:
	DeployDOT(DOT_Topology* dotTopology, InstantitiateSwitch*  instantitiatedSwitch,
			InstantitiateLink* instantitiatedLink, InstantitiateHost* instantitiatedHost,
			CommandExecutor* commandExecutor);
	virtual ~DeployDOT();
	void deploySwitch();
	void deployVMs();
	void deployLinks();
	void deployTunnel();
	void assignPortNumbers();
	void assignStaticRules();
	void createLogicalTopology();
	void createIPMACForController();
	void startController();

};

#endif /* DEPLOYDOT_H_ */
