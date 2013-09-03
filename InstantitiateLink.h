/*
 * InstantitiateLink.h
 *
 *  Created on: 2013-08-28
 *      Author: ar3roy
 */

#ifndef INSTANTITIATELINK_H_
#define INSTANTITIATELINK_H_
#include "CommandExecutor.h"
#include "Link.h"

class InstantitiateLink {
protected:
	CommandExecutor* commandExec;
public:
	InstantitiateLink(CommandExecutor* commandExec);
	virtual ~InstantitiateLink();
	void virtual createLink(Link* newLink)=0;
};

#endif /* INSTANTITIATELINK_H_ */
