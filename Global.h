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
 * Global.h
 *
 *  Created on: 2014-02-26
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "Credentials.h"
#include "PhysicalMachines.h"
#include "InputTopology.h"
#include "Hosts.h"
#include "Mapping.h"
#include "Controllers.h"
#include "Switch2Controller.h"
#include "CommandExecutor.h"
#include "InstantitiateSwitch.h"
#include "InstantitiateLink.h"
#include "InstantitiateHost.h"
#include <log4cxx/logger.h>
#include <map>
#include <string>
#include <cstdio>

using namespace log4cxx;
using namespace std;
/* 
* 
*/

class Global {

public:
    static map<string, LoggerPtr> loggerMap; 
    static string MasterName;
    static string MasterIP;
    static Credentials* credentials;
    static InputTopology* inputTopology;
    static PhysicalMachines* physicalMachines;
    static Hosts* hosts;
    static Mapping* mapping;
    static Controllers* controllers;
    static Switch2Controller* sw2controller;
    static CommandExecutor* commandExecutor;
    static InstantitiateSwitch*  instantitiatedSwitch;
    static InstantitiateLink* instantitiatedLink;
    static InstantitiateHost* instantitiatedHost;
};

#endif /* GLOBAL_H_ */

