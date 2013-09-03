/*
 * CutEdge.h
 *
 *  Created on: 2013-08-13
 *      Author: ar3roy
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
