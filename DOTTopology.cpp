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
 * DOTTopology.cpp
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "DOTTopology.h"
#include "CutEdge.h"
#include <sstream>
#include <cmath>
#include <iostream>
#include "Util.h"
using namespace std;

DOT_Topology* DOT_Topology::instanceDOT_Topology = NULL;


DOT_Topology::DOT_Topology(LogicalTopology * logicalTopology, PhysicalMachines* physicalMachines,
        Mapping* mapping, Switch2Controller * switch2Controller, VMs* vms, AbstractVM* abstractVM) {

    this->logicalTopology = logicalTopology;
    this->physicalMachines = physicalMachines;
    this->mapping = mapping;
    this->switch2Controller = switch2Controller;
    this->vms = vms;
    this->abstractVM = abstractVM;
}

DOT_Topology* DOT_Topology::getDOT_Topology(LogicalTopology* logicalTopology,
        PhysicalMachines* physicalMachines, Mapping* mapping,
        Switch2Controller* switch2Controller, VMs* vms, AbstractVM* abstractVM) {
    if(instanceDOT_Topology == NULL)
    {
        instanceDOT_Topology = new DOT_Topology(logicalTopology, physicalMachines, mapping, switch2Controller, vms, abstractVM);
    }
    return instanceDOT_Topology;
}

void DOT_Topology::generate() {
    //generate the topology switches
    for(unsigned long i = 0; i < this->logicalTopology->getNumberOfSwitches(); i++)
    {
        ostringstream switchName;
        switchName << "topo" << (i+1);
        Switch * newSwitch = new Switch(i, switchName.str(), this->mapping->getMachine(i),
                this->switch2Controller->getControllerIP(i), this->switch2Controller->getControllerPort(i));
        this->topologySwitchMap[switchName.str()] = newSwitch;
    }
    //generating the gateway switches
    for(unsigned int i = 0; i < this->physicalMachines->getNumberOfPhysicalMachines(); i++)
    {
        ostringstream switchName;
        switchName << "gw" << (i+1);
        unsigned long base = 15;
        base <<= 60;
        string dpid = Util::intToHexString(base+i+1, 16);
        //cout << dpid << endl;
        Switch * newSwitch = new Switch(i, switchName.str(), this->physicalMachines->getIPAddress(i), "", "", GATEWAY_SWITCH, dpid);
        this->gatewaySwitchMap[switchName.str()] = newSwitch;
        this->gatewaySwitchFromMachineMap[this->physicalMachines->getIPAddress(i)] = newSwitch;

    }

    cout << "Before Tunnel Generation" << endl;
    cout << "number of physical machine " << this->physicalMachines->getNumberOfPhysicalMachines() << endl;
    //Generating tunnels
    for(unsigned int i = 0; i < this->physicalMachines->getNumberOfPhysicalMachines() - 1; i++)
        for(unsigned int j = i+1; j < this->physicalMachines->getNumberOfPhysicalMachines(); j++)
        {
                Tunnel * newTunnel = new Tunnel();
                cout << "tunnel link id: " << newTunnel->getId() << endl;
                string IPAddressMachine1 = this->physicalMachines->getIPAddress(i);
                cout << "GW1 " << this->gatewaySwitchFromMachineMap[IPAddressMachine1]->getIPOfMachine();

                newTunnel->getInterface1()->assignToSwitch(this->gatewaySwitchFromMachineMap[IPAddressMachine1]);
                string IPAddressMachine2 = this->physicalMachines->getIPAddress(j);
                newTunnel->getInterface2()->assignToSwitch(this->gatewaySwitchFromMachineMap[IPAddressMachine2]);
                cout << " GW2 " << this->gatewaySwitchFromMachineMap[IPAddressMachine2]->getIPOfMachine() << endl;

                newTunnel->assignRemoteIPToInterface();
                cout << "tunnel between ip " << IPAddressMachine1 << " " << IPAddressMachine2 << endl;
                cout << "interface1 ip " << newTunnel->getInterface1()->getSwitch()->getIPOfMachine() << " ";
                cout << "interface2 ip " << newTunnel->getInterface2()->getSwitch()->getIPOfMachine() << endl;

                this->tunnelMap[make_pair(IPAddressMachine1, IPAddressMachine2)] = newTunnel;
                this->tunnelMap[make_pair(IPAddressMachine2, IPAddressMachine1)] = newTunnel;

                this->interfaceMap[make_pair(newTunnel->getInterface1()->getSwitch(), newTunnel->getInterface1()->getName())]
                                   = newTunnel->getInterface1();
                this->interfaceMap[make_pair(newTunnel->getInterface2()->getSwitch(), newTunnel->getInterface2()->getName())]
                                                   = newTunnel->getInterface2();
        }

    cout << "Tunnel Generated" << endl;

    unsigned int cutEdgeId = 0;
    //generating the links
    for(unsigned long i = 0; i < this->logicalTopology->getNumberOfSwitches()-1; i++)
        for(unsigned long j = i+1; j < this->logicalTopology->getNumberOfSwitches(); j++)
        {
            if(this->logicalTopology->getLinkBandwidth(i,j) != 0)
            {
                string IPAddressMachine1 = this->mapping->getMachine(i);
                string IPAddressMachine2 = this->mapping->getMachine(j);
                //cout << i << ": " << IPAddressMachine1 << " " << j << ": " << IPAddressMachine2 << endl;

                //Same partition
                if(IPAddressMachine1.compare(IPAddressMachine2) == 0)
                {
                        Link* newLink = new Link(this->logicalTopology->getLinkBandwidth(i,j), this->logicalTopology->getLinkDelay(i, j));

                        ostringstream switchName;
                        switchName << "topo" << (i+1);
                        newLink->getInterface1()->assignToSwitch(this->topologySwitchMap[switchName.str()]);

                        switchName.str("");
                        switchName << "topo" << (j+1);
                        newLink->getInterface2()->assignToSwitch(this->topologySwitchMap[switchName.str()]);
                        cout << "link id: " << newLink->getId() << endl;
                        this->linkMap[newLink->getId()] = newLink;

                        this->interfaceMap[make_pair(newLink->getInterface1()->getSwitch(), newLink->getInterface1()->getName())]
                                                           = newLink->getInterface1();
                        this->interfaceMap[make_pair(newLink->getInterface2()->getSwitch(), newLink->getInterface2()->getName())]
                                                                           = newLink->getInterface2();

                }
                else
                {

                    cutEdgeId++;

                    Tunnel* tunnelBetweenMachines = this->tunnelMap[make_pair(IPAddressMachine1, IPAddressMachine2)];
                    cout << i << ": " << IPAddressMachine1 << " " << j << ": " << IPAddressMachine2 << endl;
                    cout << "Tunnel in Cutedge create: ";
                    cout << tunnelBetweenMachines->getInterface1()->getSwitch()->getIPOfMachine() << " ";
                    cout << tunnelBetweenMachines->getInterface2()->getSwitch()->getIPOfMachine() << endl;

                    //create two virtual links
                    CutEdge* newLink1 = new CutEdge(this->logicalTopology->getLinkBandwidth(i,j), tunnelBetweenMachines, this->logicalTopology->getLinkDelay(i, j));
                    newLink1->cut_edge_id = cutEdgeId;
                    ostringstream switchName;
                    switchName << "topo" << (i+1);
                    newLink1->getInterface1()->assignToSwitch(this->topologySwitchMap[switchName.str()]);

                    newLink1->getInterface2()->assignToSwitch(this->gatewaySwitchFromMachineMap[IPAddressMachine1]);

                    this->linkMap[newLink1->getId()] = newLink1;
                    this->interfaceMap[make_pair(newLink1->getInterface1()->getSwitch(), newLink1->getInterface1()->getName())]
                                                           = newLink1->getInterface1();
                    this->interfaceMap[make_pair(newLink1->getInterface2()->getSwitch(), newLink1->getInterface2()->getName())]
                                                           = newLink1->getInterface2();
                    cout << "cut edge1 link id: " << newLink1->getId() << endl;
                    CutEdge* newLink2 = new CutEdge(this->logicalTopology->getLinkBandwidth(i,j), tunnelBetweenMachines, 0); //Only one of the cut edge will have the delay
                    newLink2->cut_edge_id = cutEdgeId;

                    switchName.str("");
                    switchName << "topo" << (j+1);
                    newLink2->getInterface1()->assignToSwitch(this->topologySwitchMap[switchName.str()]);

                    newLink2->getInterface2()->assignToSwitch(this->gatewaySwitchFromMachineMap[IPAddressMachine2]);
                    cout << "cut edge2 link id: " << newLink2->getId() << endl;

                    this->linkMap[newLink2->getId()] = newLink2;

                    this->interfaceMap[make_pair(newLink2->getInterface1()->getSwitch(), newLink2->getInterface1()->getName())]
                                                                   = newLink2->getInterface1();
                    this->interfaceMap[make_pair(newLink2->getInterface2()->getSwitch(), newLink2->getInterface2()->getName())]
                                                                               = newLink2->getInterface2();

                    //assign cut edge to tunnel
                    tunnelBetweenMachines->assignCutEdges(newLink1, newLink2);

                    this->cutEdgesPairVector.push_back(make_pair(newLink1, newLink2));


                }
            }

        }

    cout << "Link Generated" << endl;
    //vms generation
    for(unsigned long i = 0; i < this->vms->getNumberOfVMs(); i++)
    {
        unsigned long switchId = this->vms->getSwitch(i);
        ostringstream switchName;
        switchName << "topo" << (switchId+1);
        Switch* attachedToSwitch = this->topologySwitchMap[switchName.str()];


        ostringstream interfaceName;
        interfaceName << this->abstractVM->tapInterfacePrefix();
        interfaceName << attachedToSwitch->getNewVMAttachementPoint();


        Interface* newInterface = new Interface(interfaceName.str(), TAP);
        newInterface->assignToSwitch(attachedToSwitch);

        this->interfaceMap[make_pair(attachedToSwitch, interfaceName.str())] = newInterface;

    }

    cout << "DOT Generated" << endl;

}

DOT_Topology::~DOT_Topology() {

    for(map<unsigned long, Link*>::iterator iterator = this->linkMap.begin();
            iterator != this->linkMap.end(); iterator++)
    {
        delete iterator->second;
    }

    for(map<pair<string, string>, Tunnel* >::iterator iterator = this->tunnelMap.begin();
                iterator != this->tunnelMap.end(); iterator++)
    {
            delete iterator->second;
    }

    for(map<string, Switch*>::iterator iterator = this->topologySwitchMap.begin();
            iterator != this->topologySwitchMap.end(); iterator++)
    {
        delete iterator->second;
    }


    for(map<string, Switch*>::iterator iterator = this->gatewaySwitchMap.begin();
            iterator != this->gatewaySwitchMap.end(); iterator++)
    {
        delete iterator->second;
    }

}

