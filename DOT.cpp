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
 * main.cpp
 *
 *  Created on: 2013-03-18
 *      Author: ar3roy
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <float.h>
#include <map>
#include <sstream>
#include "PartitioningAlgorithm.h"
#include "SA.h"
#include "SA_Weighted.h"
#include "CommandExecutor.h"
#include "InputTopology.h"
#include "PhysicalMachines.h"
#include "Configurations.h"
#include "Util.h"
#include "Hosts.h"
#include "Controllers.h"
#include "Credentials.h"
#include "InstantitiateHost.h"
#include "LibvirtAttachment.h"
#include "Switch2Controller.h"
#include "GuranteedEmbedding.h"
#include "Switch.h"
#include "Tunnel.h"
#include "Interface.h"
#include "CutEdge.h"
#include "DOTTopology.h"
#include "PartitionAnalyzer.h"
#include "InstantitiateHost.h"
#include "InstantitiateLink.h"
#include "InstantitiateSwitch.h"
#include "OVS_1_9.h"
#include "VLink.h"
#include "DeployDOT.h"


using namespace std;


void prepare(string globalConfFile)
{
	Configurations *globalConf = Configurations::getConfiguration(globalConfFile);

	InputTopology *inputTopology = InputTopology::getInputTopology();
	inputTopology->populateTopology(globalConf->logicalTopologyFile);

	PhysicalMachines * physicalEnvironment = PhysicalMachines::getPhysicalMachines();
	physicalEnvironment->populateMachines(globalConf->physicalTopologyFile);
	{
		if(globalConf->delayBetweenPhysicalMachine)
		{
			physicalEnvironment->populateDelay(globalConf->physicalMachineDelayFile);
		}

	}

	cout << "Dealy: " << physicalEnvironment->getDelay(0, 1) << endl;
	cout << "Dealy: " << physicalEnvironment->getDelay(1, 1) << endl;
	Hosts* hosts = Hosts::getHosts();
	hosts->populateHosts(globalConf->hostInfoFile);
	//cout << "here" << endl;

	//cout << "IP: " << phy->getPhysicalMachines().getIPAddress("cn212") << endl;
	//cout << "IP: " << physicalEnvironment->getIPAddress("cn212") << endl;
	Mapping * mapping = Mapping::getMapping();
	mapping = mapping->getMapping();


	PartitioningAlgorithm * partitioning;
	if(globalConf->partitioningAlgorithm.compare("SA") == 0)
		partitioning = new SA(globalConf->partitioningAlgoConfFile, inputTopology, physicalEnvironment, mapping);
	else if(globalConf->partitioningAlgorithm.compare("SA_Weighted") == 0)
		partitioning = new SA_Weighted(globalConf->partitioningAlgoConfFile, inputTopology, physicalEnvironment, mapping, hosts);
	else if(globalConf->partitioningAlgorithm.compare("Guaranteed_Embedding") == 0)
			partitioning = new GuranteedEmbedding(globalConf->partitioningAlgoConfFile, inputTopology, physicalEnvironment, mapping, hosts);

	partitioning->run();
	// << "IP: " << physicalEnvironment->getIPAddress("cn212") << endl;
	for(unsigned long i = 0; i < inputTopology->getInputTopology()->getNumberOfSwitches(); i++)
		cout << "Mapping: " << i << " " << mapping->getMapping()->getMachine(i) << endl;


	PartitionAnalyzer analyzer(physicalEnvironment, mapping, inputTopology);


	//cout << hosts->getIPAddress(0) << " " << hosts->getMacAddress(0) << endl;

	Controllers* controllers = Controllers::getControllers();
	controllers->populateControllers(globalConf->controllerInfoFile);

	Switch2Controller* sw2controller = Switch2Controller::getSwitch2Controller(controllers);
	sw2controller->loadConfiguration(globalConf->switch2ControllerFile);

	cout << "controller: " <<  sw2controller->getControllerIP(1) << endl;


	cout << controllers->getIPAddress(1) << " " << controllers->getPort(1) << endl;

	Credentials* credentials = Credentials::getCredentials();
	credentials->populateCredentials(globalConf->credentialFile);
	cout << credentials->getUserName() << " " << credentials->getPassword() << " " << credentials->getKeyName() << endl;

	CommandExecutor commandExecutor(credentials, globalConf->masterIPAddress, globalConf->masterName);

	//cout << commandExecutor.executeRemote("nsm2.cs.uwaterloo.ca", "ls") << endl;
	//commandExecutor.executeLocal("~/temp.sh 100md08");
	//commandExecutor.copyContent("localhost", "nsm2.cs.uwaterloo.ca", "~/Music/mp3.temp", "~/");
	//commandExecutor.copyContent("localhost", "nsm2.cs.uwaterloo.ca", "~/Music", "~/", true);
	//commandExecutor.copyContent( "nsm2.cs.uwaterloo.ca", "localhost", "~/migration", "~/", true);
	//commandExecutor.copyContent( "nsm2.cs.uwaterloo.ca", "localhost", "~/Portal/about.html", "~/");
	//cout << commandExecutor.executeScriptLocal("~/", "temp.sh", "100");
	//cout << commandExecutor.executeScriptRemote("nsm2.cs.uwaterloo.ca", "~/", "temp.sh", "1000k");
	//commandExecutor.executeLocal("~/temp.sh 100md");
	InstantitiateSwitch*  instantitiatedSwitch = new OVS_1_9(&commandExecutor);
	InstantitiateLink* instantitiatedLink = new VLink(&commandExecutor);
	InstantitiateHost* instantitiatedHost = new LibvirtAttachment(globalConf, hosts, &commandExecutor, inputTopology, mapping);

	//cout << hostAttachment->tapInterfacePrefix() << endl;
	//hostAttachment->startHost();
	//cout << Util::intToHexString(27,4)<<endl;
	/*Switch switch1(1, "br1", mapping->getMachine(0));
	Switch switch2(2, "g1", mapping->getMachine(0), GATEWAY_SWITCH);
	Switch switch3(1, "br2", mapping->getMachine(1));
	Switch switch4(2, "g2", mapping->getMachine(1), GATEWAY_SWITCH);
	cout << switch1.getDPID() << endl;
	cout << switch1.getType() << endl;


	Interface int1("veth0", &switch1, VETH);
	Interface int2("veth1", &switch2, VETH);

	Interface int3("gre01", &switch2, GRE);
	Interface int4("gre10", &switch4, GRE);

	Tunnel tunnel(&int3, &int4);

	CutEdge cEdge(100, &int1, &int2, &tunnel);
	cout << cEdge.getCutEdgeId() << " "<<  cEdge.getAttachedTunnel()->remoteIP(&cEdge) << endl;

	cout << tunnel.getType() << " " << tunnel.remoteIP(&cEdge) << endl;
	//cout << cEdge.getCutEdgeId() << " "<<  cEdge.getAttachedTunnel()->getRemoteIP() << endl;

	*/

	DOT_Topology* dotTopology = DOT_Topology::getDOT_Topology(inputTopology, physicalEnvironment,
			mapping, sw2controller, hosts, instantitiatedHost);
	dotTopology->generate();

	DeployDOT *deploy = new DeployDOT(dotTopology, instantitiatedSwitch, instantitiatedLink, instantitiatedHost,  &commandExecutor);


	/*cout << Util::getFileName("~/hello/nothing") << endl;
	cout << Util::getFileName("~/hello/nothing.cpp") << endl;
	cout << Util::getFileName("/hello/nothing") << endl;
	cout << Util::getFileName("/hello/nothing.cpp") << endl;
	cout << Util::getFileName("~/hello/something/nothing") << endl;
	cout << Util::getFileName("~/hello/something/nothing.cpp") << endl;


	cout << Util::getPathName("~/hello/nothing") << endl;
	cout << Util::getPathName("~/hello/nothing.cpp") << endl;
	cout << Util::getPathName("/hello/nothing") << endl;
	cout << Util::getPathName("/hello/nothing.cpp") << endl;
	cout << Util::getPathName("~/hello/something/nothing") << endl;
	cout << Util::getPathName("~/hello/something/nothing.cpp") << endl;
	cout << Util::getPathName("nothing.cpp") << endl;
	cout << Util::getPathName("nothing") << endl;
	cout << Util::getPathName("~/") << endl;
	string str = Util::getPathName("~/").compare("")==0?"True":"False";
	cout << str << endl;*/

	cout << "end" <<endl;

}

void deploy()
{

}

int main(int argc, char * argv[])
{

	string globalConfFile;
	if(argc == 2 && strcmp(argv[1], "-h") == 0)
	{
		cout << "-h help" << endl <<
	  		"-g global configuration file (default: DefaultConfiguration)" << endl;
		exit(0);
	}
	else if(argc == 2 && strcmp(argv[1],"-g") == 0)
			globalConfFile = argv[2];

	else if(argc==1)
			globalConfFile = "DefaultConfiguration";
	else
		exit(1);

	//CommandExecutor executor;
	//executor.execute("ssh nsm2.cs.uwaterloo.ca \"./temp.sh arup.r.roy.tmp\"");

	prepare(globalConfFile);

	return 0;
}


