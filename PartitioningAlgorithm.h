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
 * PartitioningAlgorithm.h
 *
 *  Created on: 2013-08-12
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef PARTITIONINGALGORITHM_H_
#define PARTITIONINGALGORITHM_H_
#include <string>
#include "Mapping.h"

using namespace std;

class Mapping;
class PartitioningAlgorithm {
protected:
    void instertMapping(Mapping* mapping, string machine);
public:
    PartitioningAlgorithm();
    virtual ~PartitioningAlgorithm();
    virtual void run() = 0;
};

#endif /* PARTITIONINGALGORITHM_H_ */
