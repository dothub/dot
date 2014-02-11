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
 * OVS_1_9.h
 *
 *  Created on: 2013-08-28
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef OVS_1_9_H_
#define OVS_1_9_H_

#include "InstantitiateSwitch.h"

class OVS_1_9: public InstantitiateSwitch {
protected:
    string createClearAllRules(Switch* newSwitch);
    string createStaticTunnelRule(Switch* newSwitch, unsigned int tunnel_id, unsigned int input_port, unsigned int output_port);
public:
    OVS_1_9(CommandExecutor* commandExec);
    virtual ~OVS_1_9();
    void clearSwitch(Switch* newSwitch);
    void runSwitch(Switch* newSwitch);
    void attachPort(Switch* newSwitch, Interface* newInterface);
    void assignPortNumber(Switch* newSwitch, Interface* newInterface);
    void assignStaticTunnelRule(Switch* newSwitch, list<pair<unsigned int, pair<unsigned int, unsigned int> > > rules );
    void clearAllRules(Switch* newSwitch);

};

#endif /* OVS_1_9_H_ */
