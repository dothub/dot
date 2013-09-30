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
 * DeployDOT.cpp
 *
 *  Created on: 2013-08-28
 *      Author: ar3roy
 */

#include "DeployDOT.h"
#include <iostream>
#include <fstream>
using namespace std;

DeployDOT::DeployDOT(DOT_Topology* dotTopology, InstantitiateSwitch*  instantitiatedSwitch,
		InstantitiateLink* instantitiatedLink, InstantitiateHost* instantitiatedHost, CommandExecutor* commandExecutor)
{
	this->dotTopology = dotTopology;
	this->instantitiatedHost = instantitiatedHost;
	this->instantitiatedLink = instantitiatedLink;
	this->instantitiatedSwitch = instantitiatedSwitch;
	this->commandExecutor = commandExecutor;

	deploySwitch();
	cout << "Switch deployed" <<endl;
	deployLinks();
	cout << "link deployed" <<endl;
	deployVMs();
	cout << "VMs deployed" <<endl;
	deployTunnel();
	cout << "tunnels deployed" <<endl;
	assignPortNumbers();
	cout << "assigned port number" <<endl;
	assignStaticRules();
	cout << "static rule generated" <<endl;
	createLogicalTopology();
	cout << "topology for controller" <<endl;
	createIPMACForController();
	cout << "ipmac file for controller" <<endl;
	startController();
	cout << "controller started" <<endl;
}

DeployDOT::~DeployDOT() {

}

void DeployDOT::deploySwitch() {
	//deploy topo switch
	for( map<string, Switch*>::iterator iter = this->dotTopology->topologySwitchMap.begin();
			iter != this->dotTopology->topologySwitchMap.end(); iter++)
	{

		this->instantitiatedSwitch->clearSwitch(iter->second);
		this->instantitiatedSwitch->runSwitch(iter->second);
	}

	//deploy gateway switch
	for( map<string, Switch*>::iterator iter = this->dotTopology->gatewaySwitchMap.begin();
			iter != this->dotTopology->gatewaySwitchMap.end(); iter++)
	{
		this->instantitiatedSwitch->clearSwitch(iter->second);
		this->instantitiatedSwitch->runSwitch(iter->second);
		this->instantitiatedSwitch->clearAllRules(iter->second);
	}


}

void DeployDOT::deployVMs() {

	this->instantitiatedHost->prepare();
	cout << "Virsh Network Created" <<endl;
	for(unsigned long i = 0; i < this->dotTopology->hosts->getNumberOfHosts(); i++)
	{
		this->instantitiatedHost->startHost(i);
	}
}

void DeployDOT::deployLinks() {

	for(map<unsigned long, Link*>::iterator iter = this->dotTopology->linkMap.begin();
			iter != this->dotTopology->linkMap.end(); iter ++)
	{
		this->instantitiatedLink->createLink(iter->second);

		//assigning to ovs
		this->instantitiatedSwitch->attachPort(iter->second->getInterface1()->getSwitch(), iter->second->getInterface1());
		this->instantitiatedSwitch->attachPort(iter->second->getInterface2()->getSwitch(), iter->second->getInterface2());
	}
}

void DeployDOT::deployTunnel() {

	for(unsigned int i = 0; i < this->dotTopology->physicalMachines->getNumberOfPhysicalMachines() - 1; i++)
		for(unsigned int j = i+1; j < this->dotTopology->physicalMachines->getNumberOfPhysicalMachines(); j++)
		{
			string IPAddressMachine1 = this->dotTopology->physicalMachines->getIPAddress(i);
			string IPAddressMachine2 = this->dotTopology->physicalMachines->getIPAddress(j);

			Interface* interface1 = this->dotTopology->tunnelMap[make_pair(IPAddressMachine1, IPAddressMachine2)]->getInterface1();
			this->instantitiatedSwitch->attachPort(interface1->getSwitch(),interface1);

			Interface* interface2 = this->dotTopology->tunnelMap[make_pair(IPAddressMachine1, IPAddressMachine2)]->getInterface2();
			this->instantitiatedSwitch->attachPort(interface2->getSwitch(),interface2);

		}
}

void DeployDOT::assignPortNumbers() {

	for(map<pair<Switch*, string>, Interface* >::iterator iter = this->dotTopology->interfaceMap.begin();
			iter != this->dotTopology->interfaceMap.end(); iter++)
	{
		this->instantitiatedSwitch->assignPortNumber(iter->second->getSwitch(), iter->second);
	}
}

void DeployDOT::assignStaticRules() {

	map<Switch*, list<pair<unsigned int, pair<unsigned int, unsigned int> > > > ruleMap;
	for(vector<pair<CutEdge*, CutEdge*> >::iterator iter = this->dotTopology->cutEdgesPairVector.begin();
			 iter != this->dotTopology->cutEdgesPairVector.end(); iter++)
	{
		string IPAddressMachine1 = iter->first->getInterface1()->getSwitch()->getIPOfMachine();
		string IPAddressMachine2 = iter->second->getInterface1()->getSwitch()->getIPOfMachine();
		cout << "IP of M1" << IPAddressMachine1;
		cout << "IP of M2" << IPAddressMachine2 << endl;

		Interface* tunnelInterfaceMachine1 = iter->first->getAttachedTunnel()->getInterface1();
		Interface* tunnelInterfaceMachine2 = iter->first->getAttachedTunnel()->getInterface2();

		cout << "IP of tunnel interface1" << tunnelInterfaceMachine1->getSwitch()->getIPOfMachine();
		cout << "interface2 " << tunnelInterfaceMachine2->getSwitch()->getIPOfMachine() << endl;

		Interface* interMachine1;
		Interface* interMachine2;

		if(IPAddressMachine1.compare(tunnelInterfaceMachine1->getSwitch()->getIPOfMachine())==0)
		{
			interMachine1 = tunnelInterfaceMachine1;
			interMachine2 = tunnelInterfaceMachine2;
		}
		else if(IPAddressMachine2.compare(tunnelInterfaceMachine1->getSwitch()->getIPOfMachine())==0)
		{
			interMachine2 = tunnelInterfaceMachine1;
			interMachine1 = tunnelInterfaceMachine2;
		}
		else
			cout << "Tunnel Rule Generation Error" << endl;

		cout << this->instantitiatedSwitch->createStaticTunnelRule(iter->first->getInterface2()->getSwitch(), iter->first->cut_edge_id,
				iter->first->getInterface2()->port, interMachine1->port) << endl;

		cout << this->instantitiatedSwitch->createStaticTunnelRule(iter->second->getInterface2()->getSwitch(), iter->second->cut_edge_id,
						iter->second->getInterface2()->port, interMachine2->port) << endl;

		ruleMap[iter->first->getInterface2()->getSwitch()].push_back(make_pair(iter->first->cut_edge_id,
				make_pair(iter->first->getInterface2()->port, interMachine1->port)));
		ruleMap[iter->second->getInterface2()->getSwitch()].push_back(make_pair(iter->second->cut_edge_id,
						make_pair(iter->second->getInterface2()->port, interMachine2->port)));
	}

	for(map<Switch*, list<pair<unsigned int, pair<unsigned int, unsigned int> > > >::iterator iter = ruleMap.begin();
			iter != ruleMap.end(); iter++)
	{
		this->instantitiatedSwitch->assignStaticTunnelRule(iter->first, iter->second);
	}

}

void DeployDOT::createLogicalTopology() {

	ofstream fout("links.txt");

	if(fout.is_open())
	{
		//cout << "For internal edges" << endl;
		for(map<unsigned long, Link*>::iterator iter = this->dotTopology->linkMap.begin();
				iter != this->dotTopology->linkMap.end(); iter ++)
		{
			if(iter->second->getType() != CUT_EDGE)
			{
			fout << iter->second->getInterface1()->getSwitch()->getDPID() << " " << iter->second->getInterface1()->port
					<< " " << iter->second->getInterface2()->getSwitch()->getDPID() << " " << iter->second->getInterface2()->port << endl;
			}
		}

		//cout << "For cut edges" << endl;
		for(vector<pair<CutEdge*, CutEdge*> >::iterator iter = this->dotTopology->cutEdgesPairVector.begin();
					 iter != this->dotTopology->cutEdgesPairVector.end(); iter++)
		{
			fout << iter->first->getInterface1()->getSwitch()->getDPID() << " " << iter->first->getInterface1()->port
								<< " " << iter->second->getInterface1()->getSwitch()->getDPID() << " " << iter->second->getInterface1()->port << endl;
		}

		fout.close();
		this->commandExecutor->executeLocal("cp links.txt ~/floodlight/links.txt");
	}
	else
		cout << "~/floodlight/links.txt cannot be created" << endl;
}



void DeployDOT::createIPMACForController() {

	ofstream fout("ipMac.txt");

	if(fout.is_open())
	{
		for(unsigned long i = 0; i < this->dotTopology->hosts->getNumberOfHosts(); i++)
		{
			fout << this->dotTopology->hosts->getIPAddress(i) << " " << this->dotTopology->hosts->getMacAddress(i) << endl;
		}
		fout.close();
		this->commandExecutor->executeLocal("cp ipMac.txt ~/floodlight/ipMac.txt");
	}
	else
		cout << "~/floodlight/ipMac.txt cannot be created" << endl;


}

void DeployDOT::startController() {


	this->commandExecutor->executeLocal("sudo kill `sudo lsof -t -i:6633`");
	this->commandExecutor->executeLocal("java -jar ~/floodlight/target/floodlight.jar -cf ~/floodlight/src/main/resources/floodlightdefault.properties&");
}


