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
 * Link.cpp
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "Link.h"
#include <sstream>
#include "Global.h"

using namespace std;

unsigned long Link::id_counter = 0;
unsigned long Link::veth_counter = 0;
unsigned long Link::tunnel_counter= 0;


Link::Link(double bandwidth, double delay, LinkType type){

    this->selfLogger = Global::loggerFactory->getLogger("Link");

    this->id = id_counter++;
    if(type == TOPO_LINK || type == CUT_EDGE)
    {
        ostringstream name;
        name << "veth" << (2*veth_counter);
        this->interface1 = new Interface(name.str(),VETH);
        name.str("");
        name << "veth" << (2*veth_counter+1);
        this->interface2 = new Interface(name.str(),VETH);
        veth_counter++;
    }
    this->type = type;
    this->bandwidth = bandwidth;
    this->delay = delay;
}

LinkType Link::getType() {
    return this->type;
}

double Link::getDelay() {
    return this->delay;
}

double Link::getBandwidth() {
    return this->bandwidth;
}

unsigned long Link::getId() {
    return this->id;
}

Interface* Link::getInterface1() {
    return this->interface1;
}

Interface* Link::getInterface2() {
    return this->interface2;
}

Link::~Link() {
    // TODO Auto-generated destructor stub
}

