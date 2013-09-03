/*
 * Link.cpp
 *
 *  Created on: 2013-08-13
 *      Author: ar3roy
 */

#include "Link.h"
#include <sstream>
using namespace std;

unsigned long Link::id_counter = 0;
unsigned long Link::veth_counter = 0;
unsigned long Link::tunnel_counter= 0;


Link::Link(double bandwidth, double delay, LinkType type){
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

