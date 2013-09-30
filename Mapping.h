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
 * Mapping.h
 *
 *  Created on: 2013-08-07
 *      Author: ar3roy
 */

#ifndef MAPPING_H_
#define MAPPING_H_
#include "PartitioningAlgorithm.h"
#include <string>
#include <vector>

using namespace std;

class PartitioningAlgorithm;

class Mapping {

	Mapping();
	static Mapping* mapping;

	vector<string> switch2machine;

	void instertMapping(string machine);

	friend class PartitioningAlgorithm;

public:
	static Mapping* getMapping();

	string getMachine(unsigned long switchID);

	virtual ~Mapping();


};

#endif /* MAPPING_H_ */
