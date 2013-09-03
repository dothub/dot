/*
 * CutEdge.cpp
 *
 *  Created on: 2013-08-13
 *      Author: ar3roy
 */

#include "CutEdge.h"


CutEdge::CutEdge(double bandwidth, Tunnel * belongsToTunnel, double delay)
	:Link(bandwidth, delay, CUT_EDGE){

	this->belongsToTunnel = belongsToTunnel;
}



Tunnel* CutEdge::getAttachedTunnel() {
	return this->belongsToTunnel;
}

CutEdge::~CutEdge() {
}

