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
 *      Author: ar3roy
 */

#ifndef TUNNEL_H_
#define TUNNEL_H_

#include "Link.h"
#include "CutEdge.h"
#include <string>
#include <map>


using namespace std;

class CutEdge;

class Tunnel: public Link{
	unsigned int cutEdgeCounter;
	map<unsigned int, pair<CutEdge*, CutEdge*> > cutEdgeMap;
public:
	Tunnel(LinkType type = GRE_TUNNEL);
	unsigned int assignCutEdges(CutEdge * cutEdge1, CutEdge* cutEdge2);
	pair<CutEdge*, CutEdge*>  getCutEdges(unsigned int cutEdgeId);
	void assignRemoteIPToInterface();
	string remoteIP(Link* cutEdge);
	virtual ~Tunnel();
};

#endif /* TUNNEL_H_ */
