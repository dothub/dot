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
 * CutEdge.h
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef CUTEDGE_H_
#define CUTEDGE_H_

#include "Link.h"
#include <string>
#include "Tunnel.h"
#include "Global.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

using namespace std;

class Tunnel;


/**
* This class extends the link class to provide additonal feature for Cross-host links.
*/
class CutEdge: public Link {
   /**
    * The event logger of this class.
    */
    LoggerPtr* selfLogger;
    /**
    * The tunnel to which the cross-host link belongs
    */
    Tunnel * belongsToTunnel;
public:
    /**
    * Constructor of the class.
    * @param bandwidth - Bandwidth in Mbps.
    * @param belongsToTunnel - The tunnel to which the cut edge belongs to
    * @param delay - Propagation delay in ms (Default: 0)
    */
    CutEdge(double bandwidth, Tunnel * belongsToTunnel, double delay = 0);
    
    /**
    * @return Returns the id of a  cut edge
    */

    unsigned int getCutEdgeId();
    
    /**
    * This function is used for retrieving the Tunnel of a cut edge 
    * @return Returns the tunnel to which a cut edge is assigned.
    */
    Tunnel * getAttachedTunnel();
    friend class Tunnel;
    
    /**
    * Destructor of the class.
    */
    virtual ~CutEdge();
    /**
    * The cut edge id
    */
    unsigned int cut_edge_id;
};



#endif /* CUTEDGE_H_ */
