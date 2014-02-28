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
 * Link.h
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef LINK_H_
#define LINK_H_
#include "Interface.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

class Interface;

enum LinkType { TOPO_LINK, CUT_EDGE, GRE_TUNNEL };

class Link {
    LoggerPtr* selfLogger;

protected:
    static unsigned long id_counter;
    static unsigned long veth_counter;
    static unsigned long tunnel_counter;
    unsigned long id;
    double delay;
    double bandwidth;
    LinkType type;

protected:
    Interface* interface1;
    Interface* interface2;

public:
    Link(double bandwidth, double delay = 0, LinkType type = TOPO_LINK);
    Interface* getInterface1();
    Interface* getInterface2();
    LinkType getType();
    double getDelay();
    double getBandwidth();
    unsigned long getId();
    virtual ~Link();
};

#endif /* LINK_H_ */
