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
 * HostAttachment.h
 *
 *  Created on: 2013-08-12
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef ABSTRACTVM_H
#define ABSTRACTVM_H
#include <string>
#include "VMs.h"
#include "Configurations.h"
#include "CommandExecutor.h"
#include "LogicalTopology.h"
#include "Mapping.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "Global.h"

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;



using namespace std;


/**
* This is the base class for provisioning VM with different hypervisor library.
*/
class AbstractVM {
    /**
    * The event logger of this class.
    */
    LoggerPtr* selfLogger;

protected:
    Configurations* globalConf;
    VMs* vms;
    CommandExecutor* commandExec;
    Mapping* mapping;
    LogicalTopology* topology;
    
    /**
    * The virtual function to create the configuration to attach a VM to VSs.
    */
    virtual void createHost2SwitchAttachmentConf()=0;
    /**
    * The virtual function to load the configuration to attach a VM to VSs.
    */
    virtual void loadConfiguration(string fileName)=0;

public:
    /**
    * Constructor of the class.
    * @param - globalConf - Pointer to global configuration
    * @param - vms - Pointer to VMs of the logical toplogy
    * @param commandExec - Pointer to the CommandExecutor.
    * @param topology - Pointer to logical toplogy
    * @param mapping - Pointer to switch to physical machine mapping
    */
    AbstractVM(Configurations* globalConf, VMs* vms, 
        CommandExecutor* commandExec,   LogicalTopology * topology, Mapping* mapping);

    /**
    * Virtual function for preprocessing task.
    */
    virtual void prepare()=0;
    /**
    * The virtual function to provide an interface to deploy a VM.
    * @param: host_id - VM id
    */
    virtual void startHost(unsigned long host_id)=0;
   
    /**
    * The virtual function to provide an interface to retrieve the prefix used for tap.
    * @return - Prefix as a string
    */ 
    virtual string tapInterfacePrefix()=0;

    /**
    * The virtual function to Provide an interface to retrieve the interface name of the tap.
    * @param: host_id - VM id
    */ 

    virtual void retrieveInterface(unsigned long host_id)=0;

    /**
    * Destructor of the class.
    */
    virtual ~AbstractVM();
};

#endif /* ABSTRACTVM_H */
