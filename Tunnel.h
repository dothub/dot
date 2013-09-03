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
