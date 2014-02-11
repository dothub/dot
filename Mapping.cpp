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
 * Mapping.cpp
 *
 *  Created on: 2013-08-07
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "Mapping.h"
#include <iostream>

Mapping* Mapping::mapping = NULL;

Mapping* Mapping:: getMapping()
{
    if(mapping == NULL)
        mapping = new Mapping();

    return mapping;
}

Mapping::Mapping() {

}

string Mapping::getMachine(unsigned long switchID) {

    if(switchID < 0 || switchID >= this->switch2machine.size())
    {
        cout << "No switch found with the id: " << switchID << endl;
        return "None";
    }

    return this->switch2machine[switchID];
}

void Mapping::instertMapping(string machine) {

    this->switch2machine.push_back(machine);

}

Mapping::~Mapping() {

}

