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
 * DeployDOT.h
 *
 *  Created on: 2013-08-28
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef DEPLOYDOT_H_
#define DEPLOYDOT_H_
#include "DOTTopology.h"
#include "InstantitiateSwitch.h"
#include "InstantitiateLink.h"
#include "InstantitiateHost.h"

class DOT_Topology;

class DeployDOT {

    DOT_Topology* dotTopology;
    InstantitiateSwitch*  instantitiatedSwitch;
    InstantitiateLink* instantitiatedLink;
    InstantitiateHost* instantitiatedHost;
    CommandExecutor* commandExecutor;

public:
    DeployDOT(DOT_Topology* dotTopology, InstantitiateSwitch*  instantitiatedSwitch,
            InstantitiateLink* instantitiatedLink, InstantitiateHost* instantitiatedHost,
            CommandExecutor* commandExecutor);
    virtual ~DeployDOT();
    void deploySwitch();
    void deployVMs();
    void deployLinks();
    void deployTunnel();
    void assignPortNumbers();
    void assignStaticRules();
    void createLogicalTopology();
    void createIPMACForController();
    void startController();

};

#endif /* DEPLOYDOT_H_ */
