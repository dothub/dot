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
 * Global.cpp
 *
 *  Created on: 2014-02-26
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */


#include "Global.h"

map<string, LoggerPtr> Global::loggerMap;
string Global::MasterName = "";
string Global::MasterIP = "";
Credentials* Global::credentials = NULL;
InputTopology* Global::inputTopology = NULL;
PhysicalMachines* Global::physicalMachines = NULL;
Hosts* Global::hosts = NULL;
Mapping* Global::mapping = NULL;
Controllers* Global::controllers = NULL;
Switch2Controller* Global::sw2controller = NULL;
CommandExecutor* Global::commandExecutor = NULL;
InstantitiateSwitch*  Global::instantitiatedSwitch = NULL;
InstantitiateLink* Global::instantitiatedLink = NULL;
InstantitiateHost* Global::instantitiatedHost = NULL;

