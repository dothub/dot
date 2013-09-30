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
