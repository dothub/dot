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
 * Tunnel.h
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef TUNNEL_H_
#define TUNNEL_H_

#include "Link.h"
#include "CutEdge.h"
#include <string>
#include <map>
#include "Global.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

using namespace std;

class CutEdge;

/**
* This class extends the Link class for providing additional features for Tunnel.
*/
class Tunnel: public Link{
    
    LoggerPtr* selfLogger;
    
    unsigned int cutEdgeCounter;
    map<unsigned int, pair<CutEdge*, CutEdge*> > cutEdgeMap;
public:
    /**
    * Constructor of the class.
    * @param type - Link type (Default: GRE_LINK)
    */
    Tunnel(LinkType type = GRE_TUNNEL);
   
    /**
    * This function assigns a pair of cut edges belonging to the tunnel.
    * @param cutEdge1 - One cut edge of the pair
    * @param cutEdge2 - Another cut edge of the pair 
    */
    unsigned int assignCutEdges(CutEdge * cutEdge1, CutEdge* cutEdge2);
    
    /**
    * This function retrieve a cut edge pair from its id.
    * @param cutEdgeId - Id of a cut edge pair
    * @return - CutEdge pair 
    */  
    pair<CutEdge*, CutEdge*>  getCutEdges(unsigned int cutEdgeId);
    
    /**
    * This function assigns ip address of the remote machine to the tunnel.
    */  
    void assignRemoteIPToInterface();
    
    /**
    * This function returns the ip address of the remote machine for a cut edge
    * @param cutEdge - Pointer to a cut edge
    * @return - IP Address as a string    */

    string remoteIP(Link* cutEdge);
    
    /**
    * Destructor of the class.
    */
    virtual ~Tunnel();
};

#endif /* TUNNEL_H_ */
