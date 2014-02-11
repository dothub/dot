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

using namespace std;

class Tunnel;

class CutEdge: public Link {

    Tunnel * belongsToTunnel;
public:
    CutEdge(double bandwidth, Tunnel * belongsToTunnel, double delay = 0);
    unsigned int getCutEdgeId();
    Tunnel * getAttachedTunnel();
    friend class Tunnel;
    virtual ~CutEdge();
    unsigned int cut_edge_id;
};

#endif /* CUTEDGE_H_ */
