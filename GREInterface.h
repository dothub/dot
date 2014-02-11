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
 * GREInterface.h
 *
 *  Created on: 2013-08-28
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef GREINTERFACE_H_
#define GREINTERFACE_H_

#include "Interface.h"

class GRE_Interface: public Interface {

public:
    string remoteIP;
    GRE_Interface(string name);
    string getRemoteIP();
    virtual ~GRE_Interface();
};

#endif /* GREINTERFACE_H_ */
