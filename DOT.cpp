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
 * DOT.cpp
 *
 *  Created on: 2013-03-18
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <float.h>
#include <map>
#include <sstream>
#include "PartitioningAlgorithm.h"
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
    partitioning = new GuranteedEmbedding(globalConf->partitioningAlgoConfFile, 
        inputTopology, physicalEnvironment, mapping, hosts);

    if( partitioning->run() == false)
    {
        cout << "Embedding is not successful" << endl;
        return;
    }
        
    // << "IP: " << physicalEnvironment->getIPAddress("cn212") << endl;
    for(unsigned long i = 0; i < inputTopology->getInputTopology()->getNumberOfSwitches(); i++)
        cout << "Mapping: " << i << " " << mapping->getMapping()->getMachine(i) << endl;

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

    InstantitiateSwitch*  instantitiatedSwitch = new OVS_1_9(&commandExecutor);
    InstantitiateLink* instantitiatedLink = new VLink(&commandExecutor);
    InstantitiateHost* instantitiatedHost = new LibvirtAttachment(globalConf, hosts, &commandExecutor, inputTopology, mapping);

    

    DOT_Topology* dotTopology = DOT_Topology::getDOT_Topology(inputTopology, physicalEnvironment,
            mapping, sw2controller, hosts, instantitiatedHost);
    dotTopology->generate();

    DeployDOT *deploy = new DeployDOT(dotTopology, instantitiatedSwitch, instantitiatedLink, instantitiatedHost,  &commandExecutor);



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


