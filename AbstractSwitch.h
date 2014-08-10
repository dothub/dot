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
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "Global.h"

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;


/**
* This is the base class for provisioning different classes of virtual switch.
*/
class AbstractSwitch {

    /**
    * The event logger of this class.
    */
    LoggerPtr* selfLogger;
 
protected:
   /**
    * Pointer to the CommandExecutor Object.
    */
    CommandExecutor* commandExec;
    
    /**
    * This virtual function provides the command to clears all forwarding rule.
    * @param theSwitch - Pointer to the switch
    * @return string
    */
    virtual string createClearAllRules(Switch* theSwitch)=0;

public:
    /**
    * Constructor of the class.
    * @param commandExec - Pointer to the global object of CommandExecutor.
    */
    AbstractSwitch(CommandExecutor* commandExec);
    
    /**
    * This virtual function provides interface to clears all forwarding rule.
    * @param theSwitch - Pointer to the switch
    */
    virtual void clearSwitch(Switch* theSwitch)=0;
    
    /**
    * This virtual function provides interface to start a switch.
    * @param theSwitch - Pointer to the switch
    */
    virtual void runSwitch(Switch* theSwitch)=0;
    
    /**
    * This virtual function provides the functionlity to attach an Interface to a switch.
    * @param theSwitch - Pointer to the switch
    * @param newInterface - Pointer to the interface
    */
    virtual void attachPort(Switch* theSwitch, Interface* newInterface)=0;
    
    /**
    * This virtual function provides the functionlity to get port to which an Interface is attached.
    * @param theSwitch - Pointer to the switch
    * @param newInterface - Pointer to the interface
    */
    virtual void assignPortNumber(Switch* theSwitch, Interface* newInterface)=0;
   /**
    * This virtual function provides the functionlity to create static tunnel rules.
    * @param theSwitch - Pointer to the switch
    * @param tunnel_id - Tunnel tag
    * @param input_port - The input port of the flow rule
    * @param output_port - The output por of the flow rule
    * @return The rule as a string
    */
    virtual string createStaticTunnelRule(Switch* theSwitch, 
            unsigned int tunnel_id, unsigned int input_port, unsigned int output_port)=0;
    /**
    * This virtual function provides the functionlity to assign static tunnel rules.
    * @param theSwitch - Pointer to the switch
    * @param rules - A list of <tunnel id, input port, output port> encapsulated in pair
    */
    virtual void assignStaticTunnelRule(Switch* theSwitch, 
            list<pair<unsigned int, pair<unsigned int, unsigned int> > > rules )=0;
    /**
    * This virtual function provides the functionlity to clear all rules.
    * @param theSwitch - Pointer to the switch
    */
    virtual void clearAllRules(Switch* theSwitch)=0;

    /**
    * This virtual function provides the functionlity to rate limit an interface.
    * @param theSwitch - Pointer to the switch
    * @param portName - The name of the port
    * @param rate - Bandwidth in kbps
    * @param burst- Traffic burst (Default: 0)
    */
    virtual void assignQoSToPort(Switch* theSwitch, 
            string portName, unsigned long rate, unsigned long burst=0)=0; 
    
    virtual void stopL2Flood(Switch* theSwitch)=0;
    
    virtual void setOFVersion(Switch* theSwitch, string version)=0;
    
    virtual void assignIPAddress(Switch* theSwitch)=0;

    /**
    * Destructor of the class.
    */
    virtual ~AbstractSwitch();
};

#endif /* ABSTRACTSWITCH_H_ */
