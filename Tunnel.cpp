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
 * Tunnel.cpp
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "Tunnel.h"
#include "GREInterface.h"
#include <sstream>
using namespace std;

Tunnel::Tunnel(LinkType type)
: Link(0, type)
{
    this->selfLogger = Global::loggerFactory->getLogger("Tunnel");
    cutEdgeCounter = 1;

    if(type == GRE_TUNNEL)
    {
        ostringstream name;
        name << "gre" << (2*tunnel_counter);
        this->interface1 = new GRE_Interface(name.str());
        name.str("");
        name << "gre" << (2*tunnel_counter+1);
        this->interface2 = new GRE_Interface(name.str());
        tunnel_counter++;
    }

}

unsigned int Tunnel::assignCutEdges(CutEdge* cutEdge1, CutEdge* cutEdge2) {

    this->cutEdgeMap[cutEdgeCounter++] = make_pair(cutEdge1, cutEdge2);
    cutEdge1->cut_edge_id = cutEdgeCounter-1;
    cutEdge2->cut_edge_id = cutEdgeCounter-1;

    return cutEdgeCounter-1;
}

pair<CutEdge*, CutEdge*> Tunnel::getCutEdges(unsigned int cutEdgeId) {

    return this->cutEdgeMap[cutEdgeId];

}

void Tunnel::assignRemoteIPToInterface()
{
    ((GRE_Interface*)this->interface1)->remoteIP = this->interface2->getSwitch()->getIPOfMachine();
    ((GRE_Interface*)this->interface2)->remoteIP = this->interface1->getSwitch()->getIPOfMachine();
}

string Tunnel::remoteIP(Link* cutEdge) {

    string cutEdgeMachineIP = cutEdge->getInterface1()->getSwitch()->getIPOfMachine();
    string interface1MachineIP = this->interface1->getSwitch()->getIPOfMachine();
    string interface2MachineIP = this->interface2->getSwitch()->getIPOfMachine();

    if(interface1MachineIP.compare(cutEdgeMachineIP) == 0)
        return interface2MachineIP;
    else
        return interface1MachineIP;
}

Tunnel::~Tunnel() {

}

