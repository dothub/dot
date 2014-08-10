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
#include "AbstractSwitch.h"
#include "AbstractLink.h"
#include "AbstractVM.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

class DOT_Topology;

class DeployDOT {
    LoggerPtr* selfLogger;
    DOT_Topology* dotTopology;
    AbstractSwitch*  abstractSwitch;
    AbstractLink* abstractLink;
    AbstractVM* abstractVM;
    CommandExecutor* commandExecutor;

public:
    DeployDOT(DOT_Topology* dotTopology, AbstractSwitch*  abstractSwitch,
            AbstractLink* abstractLink, AbstractVM* abstractVM,
            CommandExecutor* commandExecutor);
    virtual ~DeployDOT();
    void deploySwitch();
    void deployVMs();
    void deployLinks();
    void deployTunnel();
    void assignPortNumbers();
    void assignStaticRules();

};

#endif /* DEPLOYDOT_H_ */
