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
#include <fstream>
#include "EmbeddingAlgorithm.h"
#include "Global.h"
#include "Configurations.h"
#include "KVMWithLibvirt.h"
#include "GuaranteedEmbedding.h"
#include "DOTTopology.h"
#include "OVS_2_1.h"
#include "DeployDOT.h"
#include "VLink.h"
#include "ImageRepo.h"
#include "OtherConfig.h"

using namespace std;

LoggerPtr* selfLogger;

bool prepare(string globalConfFile)
{
    LOG4CXX_INFO((*selfLogger), "Reading the configurations");

    Configurations *globalConf = Configurations::getConfiguration(globalConfFile);

    Global::logicalTopology = LogicalTopology::getLogicalTopology();
    Global::logicalTopology->populateTopology(globalConf->logicalTopologyFile);

    Global::physicalMachines = PhysicalMachines::getPhysicalMachines();
    Global::physicalMachines->populateMachines(globalConf->physicalTopologyFile);
    {
        if(globalConf->delayBetweenPhysicalMachine)
        {
            Global::physicalMachines->populateDelay(globalConf->physicalMachineDelayFile);
        }

    }
    
    Global::commandExecutor = new CommandExecutor(Global::credentials, 
        globalConf->masterIPAddress, globalConf->masterName);


    Global::imageRepo = new ImageRepo(Global::commandExecutor);
    Global::imageRepo->populateImages(globalConf->imageConfigFile);

    Global::vms = VMs::getVMs();
    Global::vms->populateVMs(globalConf->hostInfoFile);

    Global::controllers = Controllers::getControllers();
    Global::controllers->populateControllers(globalConf->controllerInfoFile);
    
    Global::sw2controller = Switch2Controller::getSwitch2Controller(Global::controllers);
    Global::sw2controller->loadConfiguration(globalConf->switch2ControllerFile);

    Global::credentials = Credentials::getCredentials();
    Global::credentials->populateCredentials(globalConf->credentialFile);

    Global::otherConfig = new OtherConfig();
    Global::otherConfig->populate(globalConf->otherConfigFile);
    
    Global::mapping = Mapping::getMapping();

    LOG4CXX_INFO((*selfLogger), "Embedding is started");

    EmbeddingAlgorithm * partitioning = new GuaranteedEmbedding(
        globalConf->partitioningAlgoConfFile, 
        Global::logicalTopology, Global::physicalMachines, 
        Global::mapping, Global::vms);

    if( partitioning->run() == false)
    {
        LOG4CXX_INFO((*selfLogger), 
             "Embedding is not successful");
        return false;
    }
        
    LOG4CXX_INFO((*selfLogger), "Instantiating the deployment specific devices");

    Global::abstractSwitch = new OVS_2_1(Global::commandExecutor);
    Global::abstractLink = new VLink(Global::commandExecutor);
    Global::abstractVM = new KVMWithLibvirt(globalConf, Global::vms, 
                   Global::commandExecutor, Global::logicalTopology, Global::mapping);
    
    return true;
}

void deploy()
{
    LOG4CXX_INFO((*selfLogger), "DOT Deployment has started");

    DOT_Topology* dotTopology = DOT_Topology::getDOT_Topology(Global::logicalTopology, 
               Global::physicalMachines, Global::mapping, 
               Global::sw2controller, Global::vms, Global::abstractVM);
    
    dotTopology->generate();
    LOG4CXX_INFO((*selfLogger), "DOT Topology is generated");


    DeployDOT *deploy = new DeployDOT(dotTopology, Global::abstractSwitch, 
                            Global::abstractLink, Global::abstractVM, 
                            Global::commandExecutor);

    LOG4CXX_INFO((*selfLogger), "Emulated network has been deployed ");


}


void generateMappingForRemote()
{
  
    LOG4CXX_INFO((*selfLogger), "Generating Mapping File for DOT console ");

    fstream fout("ongoing_emulation/mapping"); 
 
    fout << Global::credentials->getUserName() << endl;
 
    if(fout.is_open()) 
    { 
        for(unsigned long i = 0; i < Global::vms->getNumberOfVMs(); i++) 
        { 
            fout << "h" << i+1 << " " 
                << Global::mapping->getMapping()->getMachine(Global::vms->getSwitch(i)) << endl; 
        } 
        fout.close(); 
    } 
    else 
        LOG4CXX_ERROR((*selfLogger), 
            "Mapping file for \"DOT Console\" cannot be created"); 
}


int main(int argc, char * argv[])
{

    string globalConfFile;

    Global::loggerFactory = LoggerFactory::getLoggerFactory();
  
    selfLogger = Global::loggerFactory->getLogger("main");
    LOG4CXX_INFO((*selfLogger), "DOT main has started ");
    
    if(argc == 1 ||
        (argc == 2 && strcmp(argv[1], "-h") == 0))
    {
        cout << "-h Help" << endl <<
            "-c Configuration file" << endl
             << "-d Debug" << endl;
        exit(0);
    }
    if(argc == 3 && strcmp(argv[1],"-g") == 0)
            globalConfFile = argv[2];

    else if(argc == 4)
    {
            if(strcmp(argv[1], "-g") == 0
                && strcmp(argv[3], "-d") == 0)
            {   
                globalConfFile = argv[2];
                
                Global::debugMode = true;
                
                LOG4CXX_INFO((*selfLogger), 
                            "Debug mode on" );
                (*selfLogger)->setLevel(Level::getDebug());

            }
            else if(strcmp(argv[1], "-d") == 0
                && strcmp(argv[2], "-g") == 0)
            {
                globalConfFile = argv[3];
                Global::debugMode = true;  
                
                LOG4CXX_INFO((*selfLogger), 
                            "Debug mode on" );

                (*selfLogger)->setLevel(Level::getDebug());

            }
            
            else
                exit(1);
    }

    LOG4CXX_INFO((*selfLogger), 
           "The global configuration file: "
             << globalConfFile);
    
    if(! prepare(globalConfFile))
        exit(1);
    deploy();
    generateMappingForRemote();


    return 0;
}


