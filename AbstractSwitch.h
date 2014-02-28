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
 * AbstractSwitch.h
 *
 *  Created on: 2013-08-28
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef ABSTRACTSWITCH_H_
#define ABSTRACTSWITCH_H_
#include <string>
#include <list>
#include "Switch.h"
#include "CommandExecutor.h"
#include "Interface.h"

using namespace std;

class AbstractSwitch {
protected:
    CommandExecutor* commandExec;
    virtual string createClearAllRules(Switch* newSwitch)=0;

public:
    AbstractSwitch(CommandExecutor* commandExec);
    virtual void clearSwitch(Switch* newSwitch)=0;
    virtual void runSwitch(Switch* newSwitch)=0;
    virtual void attachPort(Switch* newSwitch, Interface* newInterface)=0;
    virtual void assignPortNumber(Switch* newSwitch, Interface* newInterface)=0;
    virtual string createStaticTunnelRule(Switch* newSwitch, unsigned int tunnel_id, unsigned int input_port, unsigned int output_port)=0;
    virtual void assignStaticTunnelRule(Switch* newSwitch, list<pair<unsigned int, pair<unsigned int, unsigned int> > > rules )=0;
    virtual void clearAllRules(Switch* newSwitch)=0;
    virtual void assignQoSToPort(Switch* newSwitch, string portName, unsigned long rate, unsigned long burst=0)=0; 
    virtual ~AbstractSwitch();
};

#endif /* ABSTRACTSWITCH_H_ */
