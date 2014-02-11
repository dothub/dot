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
 * PartitioningAlgorithm.cpp
 *
 *  Created on: 2013-08-12
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "PartitioningAlgorithm.h"

PartitioningAlgorithm::PartitioningAlgorithm() {
    // TODO Auto-generated constructor stub

}

void PartitioningAlgorithm::instertMapping(Mapping* mapping, string machine) {

    mapping->instertMapping(machine);
}

PartitioningAlgorithm::~PartitioningAlgorithm() {
    // TODO Auto-generated destructor stub
}

