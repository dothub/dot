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
 * OVS_1_10.h
 *
 *  Created on: 2013-08-28
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef OVS_1_10_H_
#define OVS_1_10_H_
#include "Global.h"
#include "AbstractSwitch.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

class OVS_1_10: public AbstractSwitch {
    /**
    * The event logger of this class.
    */
    LoggerPtr* selfLogger;

protected:
    /**
    * This function generates the rules to delete all flows.
    * @param theSwitch - Pointer to the switch
    * @return The command as a string
    */
    string createClearAllRules(Switch* theSwitch);
    
    
    /**
    * This creates the static rules for tunnel.
    * @param theSwitch - Pointer to the switch
    * @param tunnel_id - Tunnel tag
    * @param input_port - The input port of the flow rule
    * @param output_port - The output por of the flow rule
    * @return The command as a string
    */
    string createStaticTunnelRule(Switch* theSwitch, unsigned int tunnel_id, 
            unsigned int input_port, unsigned int output_port);
public:
    /**
    * Constructor of the class.
    * @param commandExec - Pointer to the global object of CommandExecutor.
    */
    OVS_1_10(CommandExecutor* commandExec);
    /**
    * Destructor of the class.
    */
    virtual ~OVS_1_10();
    /**
    * This function deletes the switch.
    * @param theSwitch - Pointer to the switch
    */
    void clearSwitch(Switch* theSwitch);
    /**
    * This function starts a switch.
    * @param theSwitch - Pointer to the switch
    */
    void runSwitch(Switch* theSwitch);
   
    /**
    * This function attaches an Interface to a switch.
    * @param theSwitch - Pointer to the switch
    * @param newInterface - Pointer to the interface
    */
    void attachPort(Switch* theSwitch, Interface* newInterface);
    /**
    * This function attaches assings port number of the switch to which the interface is attached.
    * @param theSwitch - Pointer to the switch
    * @param newInterface - Pointer to the interface
    */   
    void assignPortNumber(Switch* theSwitch, Interface* newInterface);
    /**
    * This function assigns static tunnel rules.
    * @param theSwitch - Pointer to the switch
    * @param rules - A list of <tunnel id, input port, output port> encapsulated in pair
    */
    void assignStaticTunnelRule(Switch* theSwitch, 
            list<pair<unsigned int, pair<unsigned int, unsigned int> > > rules );
    
    /**
    * This clears all rules.
    * @param theSwitch - Pointer to the switch
    */
    void clearAllRules(Switch* theSwitch);
    /**
    * This function provides rate limiting of  an interface.
    * @param theSwitch - Pointer to the switch
    * @param portName - The name of the port
    * @param rate - Bandwidth in kbps
    * @param burst- Traffic burst (Default: 0)
    */
    void assignQoSToPort(Switch* theSwitch, string portName, 
            unsigned long rate, unsigned long burst=0);
};

#endif /* OVS_1_10_H_ */
