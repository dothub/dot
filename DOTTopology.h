/*
 * DOTTopology.h
 *
 *  Created on: 2013-08-13
 *      Author: ar3roy
 */

#ifndef DOTTOPOLOGY_H_
#define DOTTOPOLOGY_H_

#include "Interface.h"
#include "Link.h"
#include "Switch.h"
#include "PhysicalMachines.h"
#include "Mapping.h"
#include "InputTopology.h"
#include "Switch2Controller.h"
#include "InstantitiateHost.h"
#include "Tunnel.h"
#include "CutEdge.h"
#include "Hosts.h"
#include "DeployDOT.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

class DeployDOT;

class DOT_Topology {

	map<unsigned long, Link*> linkMap;
	map<string, Switch*> topologySwitchMap;
	map<string, Switch*> gatewaySwitchMap;
	map<string, Switch*> gatewaySwitchFromMachineMap;
	map<pair<string, string>, Tunnel* > tunnelMap;
	map<pair<Switch*, string>, Interface* > interfaceMap;
	vector<pair<CutEdge*, CutEdge*> > cutEdgesPairVector;

	PhysicalMachines* physicalMachines;
	Mapping* mapping;
	InputTopology * inputTopology;
	Switch2Controller * switch2Controller;
	Hosts* hosts;
	InstantitiateHost* instantitiatedHost;

	static DOT_Topology* instanceDOT_Topology;

	DOT_Topology(InputTopology * inputTopology, PhysicalMachines* physicalMachines,
			Mapping* mapping, Switch2Controller * switch2Controller, Hosts* hosts, InstantitiateHost* instantitiatedHost);

	friend class DeployDOT;

public:
	static DOT_Topology* getDOT_Topology(InputTopology * inputTopology, PhysicalMachines* physicalMachines,
				Mapping* mapping, Switch2Controller * switch2Controller, Hosts* hosts, InstantitiateHost* instantitiatedHost);
	void generate();

	virtual ~DOT_Topology();



};

#endif /* DOTTOPOLOGY_H_ */
