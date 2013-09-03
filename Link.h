/*
 * Link.h
 *
 *  Created on: 2013-08-13
 *      Author: ar3roy
 */

#ifndef LINK_H_
#define LINK_H_
#include "Interface.h"

class Interface;

enum LinkType { TOPO_LINK, CUT_EDGE, GRE_TUNNEL };

class Link {
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
