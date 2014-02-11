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
 * Interface.cpp
 *
 *  Created on: 2013-08-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "Interface.h"

string Interface::getName() {
    return this->name;
}

Interface::Interface(string name, InterfaceType type) {
    this->name = name;
    this->type = type;

}
void Interface::assignToSwitch(Switch* theSwitch)
{
    this->connectedToSwitch = theSwitch;
    this->connectedToSwitch->assignInterface(this);
}
Switch* Interface::getSwitch() {
    return this->connectedToSwitch;
}

InterfaceType Interface::getType()
{
    return this->type;
}

Interface::~Interface() {
    // TODO Auto-generated destructor stub
}

