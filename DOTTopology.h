/*
* This file is part of DOT.
*
*     DOT is free software: you can redistribute it and/or modify
*     it under the terms of the GNU General Public License as published by
*     the Free Software Foundation, either version 3 of the License, or
*     (at your option) any later version.
*
*     DOT is distributed in the hope that it will be useful,
*     but WITHOUT ANY WARRANTY; without even the implied warranty of
*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*     GNU General Public License for more details.
*
*     You should have received a copy of the GNU General Public License
*     along with DOT.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright 2011-2013 dothub.org
*/

/*
 * DOTTopology.h
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef DOTTOPOLOGY_H_
#define DOTTOPOLOGY_H_

#include "Interface.h"
#include "Link.h"
#include "Switch.h"
#include "PhysicalMachines.h"
#include "Mapping.h"
#include "LogicalTopology.h"
#include "Switch2Controller.h"
#include "AbstractVM.h"
#include "Tunnel.h"
#include "CutEdge.h"
#include "VMs.h"
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
    LogicalTopology * logicalTopology;
    Switch2Controller * switch2Controller;
    VMs* vms;
    AbstractVM* instantitiatedHost;

    static DOT_Topology* instanceDOT_Topology;

    DOT_Topology(LogicalTopology * logicalTopology, PhysicalMachines* physicalMachines,
            Mapping* mapping, Switch2Controller * switch2Controller, VMs* vms, AbstractVM* instantitiatedHost);

    friend class DeployDOT;

public:
    static DOT_Topology* getDOT_Topology(LogicalTopology * logicalTopology, PhysicalMachines* physicalMachines,
                Mapping* mapping, Switch2Controller * switch2Controller, VMs* vms, AbstractVM* instantitiatedHost);
    void generate();

    virtual ~DOT_Topology();



};

#endif /* DOTTOPOLOGY_H_ */
