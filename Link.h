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
/**
* This is an enumerator for link type.
*/
enum LinkType { 
    /**Intra-host link */
    TOPO_LINK, 
    /** Cross-host link */
    CUT_EDGE, 
    /** Tunnel using GRE */
    GRE_TUNNEL 
};

/**
* This is the base class for a virtual link.
*/
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
    /**
    * Constructor of the class.
    * @param bandwidth - Bandwidth in Mbps.
    * @param delay - Propagation delay in ms (Default: 0)
    * @param type - Link type (Default: TOPO_LINK)
    */
    Link(double bandwidth, double delay = 0, LinkType type = TOPO_LINK);
    
    /**
    * Used to retrieve the first interface
    * @return Returns first interface of the link
    */
    Interface* getInterface1();
    /**
    * Used to retrieve the second interface
    * @return Returns second interface of the link
    */
    Interface* getInterface2();
    /**
    * Used to retrieve the type of the link
    * @return Returns the link type
    */    
    LinkType getType();
    /**
    * Used to retrieve the dealy of the link
    * @return Returns the link delay
    */
    double getDelay();
    /**
    * Used to retrieve the bandwidth of the link
    * @return Returns bandwidth of the link
    */
    double getBandwidth();
    /**
    * Used to retrieve the link id
    * @return Returns the link id
    */
    unsigned long getId();
    /**
    * Destructor of the class.
    */
    virtual ~Link();
};

#endif /* LINK_H_ */
