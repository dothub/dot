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
 * Configurations.cpp
 *
 *  Created on: 2013-08-06
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "Configurations.h"
#include <iostream>
#include <fstream>
#include <map>
#include "Util.h"

using namespace std;

Configurations * Configurations::configuration = NULL;

Configurations::Configurations(string configurationFileName) {
    this->globalConfigurationFile = configurationFileName;

    this->loadConfiguration();
}

Configurations* Configurations:: getConfiguration(string configurationFileName)
{
    if(configuration == NULL)
            configuration = new Configurations(configurationFileName);

    return configuration;
}

void Configurations::loadConfiguration() {

    //default values
    masterName="localhost";
    masterIPAddress = "0.0.0.0";
    logicalTopologyFile = "LogicalTopology";
    physicalTopologyFile = "PhysicalTopology";
    controllerInfoFile = "ControllerInfo";
    switch2ControllerFile = "Switch2Controller";
    hostInfoFile = "HostInfo";
    credentialFile="CredentialFile";
    partitioningAlgorithm = "SA";
    partitioningAlgoConfFile = "SA_Configuration";
    hypervisor="lib-virt";
    hypervisorConfigurationFile="lib-virt_Configuration";
    hostImage="~/Core-current.iso";
    delayBetweenPhysicalMachine = false;

    map<string, string> eachConfiguration;

    ifstream fin(this->globalConfigurationFile.c_str());

    if(fin.is_open())
    {
        while(!fin.eof())
        {
            string line, key, value;
            fin >> line;
            Util::parseKeyValue(line, key, value, '=');

            if(key.compare(""))
            {
                //cout << key << endl << value << endl;
                eachConfiguration[key] = value;
            }
        }

        fin.close();
    }
    else
        cout << "Unable to open configuration file: " << this->globalConfigurationFile <<  endl;

    //Getting the values
    if(eachConfiguration.find("MasterName") != eachConfiguration.end())
        masterName = eachConfiguration["MasterName"];

    if(eachConfiguration.find("MasterIP") != eachConfiguration.end())
        masterIPAddress = eachConfiguration["MasterIP"];

    if(eachConfiguration.find("HostImage") != eachConfiguration.end())
        hostImage = eachConfiguration["HostImage"];

    if(eachConfiguration.find("LogicalTopology") != eachConfiguration.end())
        logicalTopologyFile = eachConfiguration["LogicalTopology"];

    if(eachConfiguration.find("PhysicalTopology") != eachConfiguration.end())
        physicalTopologyFile = eachConfiguration["PhysicalTopology"];

    if(eachConfiguration.find("Controllers") != eachConfiguration.end())
        controllerInfoFile = eachConfiguration["Controllers"];

    if(eachConfiguration.find("SwitchToController") != eachConfiguration.end())
        switch2ControllerFile = eachConfiguration["SwitchToController"];

    if(eachConfiguration.find("HostConfiguration") != eachConfiguration.end())
        hostInfoFile = eachConfiguration["HostConfiguration"];

    if(eachConfiguration.find("UserCredentials") != eachConfiguration.end())
        credentialFile = eachConfiguration["UserCredentials"];

    if(eachConfiguration.find("PartitioningAlgorithm") != eachConfiguration.end())
        partitioningAlgorithm = eachConfiguration["PartitioningAlgorithm"];

    if(eachConfiguration.find("PartitioningAlgorithmConfiguration") != eachConfiguration.end())
        partitioningAlgoConfFile = eachConfiguration["PartitioningAlgorithmConfiguration"];

    if(eachConfiguration.find("HyperVisor") != eachConfiguration.end())
        hypervisor = eachConfiguration["HyperVisor"];

    if(eachConfiguration.find("HyperVisorConfiguration") != eachConfiguration.end())
        hypervisorConfigurationFile = eachConfiguration["HyperVisorConfiguration"];

    if(eachConfiguration.find("PhysicalMachineDelay") != eachConfiguration.end())
    {
        delayBetweenPhysicalMachine = true;
        physicalMachineDelayFile = "PhysicalTopologyDelay";

        if(eachConfiguration.find("PhysicalDealyFile") != eachConfiguration.end())
            physicalMachineDelayFile = eachConfiguration["PhysicalDealyFile"];
    }

}

Configurations::~Configurations() {

}

