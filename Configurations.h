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
 * Configurations.h
 *
 *  Created on: 2013-08-06
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef CONFIGURATIONS_H_
#define CONFIGURATIONS_H_

#include <string>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;

class Configurations {

    LoggerPtr* selfLogger;

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
    string embeddingAlgorithm;
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
