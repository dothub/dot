/*
 * VLink.h
 *
 *  Created on: 2013-08-28
 *      Author: ar3roy
 */

#ifndef VLINK_H_
#define VLINK_H_

#include "InstantitiateLink.h"

class VLink: public InstantitiateLink {
public:
	VLink(CommandExecutor* commandExec);
	virtual ~VLink();
	void createLink(Link* newLink);
};

#endif /* VLINK_H_ */
