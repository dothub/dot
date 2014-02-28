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
 * KVMWithLibvirt.h
 *
 *  Created on: 2013-08-12
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef KVMWITHLIBVIRT_H_
#define KVMWITHLIBVIRT_H_
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

#include "AbstractVM.h"

/**
* The class for provisioning VM with in KVM hypervisor using libvirt.
*/

class KVMWithLibvirt: public AbstractVM {
    /**
    * The event logger of this class.
    */
    LoggerPtr* selfLogger;
   /**
    * The type of the hypervisor. Here: kvm.
    */ 
    string virt_type;
    /**
    * The name of the network configuration file.
    */
    string networkFile;

    /**
    * The function to load the network.xml to attach a VM to VSs.
    */
    void loadConfiguration(string fileName);
    
    /**
    * The function to copy the default disk image for new VM.
    * @param: host_id - VM id
    * @return: Name of the image with its path
    */
    string createNewImage(unsigned long host_id);
public:
    /**
    * Constructor of the class.
    * @param - globalConf - Pointer to global configuration
    * @param - vms - Pointer to VMs of the logical toplogy
    * @param commandExec - Pointer to the CommandExecutor.
    * @param topology - Pointer to logical toplogy
    * @param mapping - Pointer to switch to physical machine mapping
    */

    KVMWithLibvirt(Configurations* globalConf, VMs* vms, CommandExecutor* commandExec, LogicalTopology *topology, Mapping* mapping);
    /**
    * The function to create the configuration to attach a VM to VSs.
    */
    void createHost2SwitchAttachmentConf();
    /**
    * The function to deploy a VM.
    * @param: host_id - VM id
    */ 
    void startHost(unsigned long host_id);
    /**
    * The function to retrieve the interface name of the tap and update the VM property
    *  @param: host_id - VM id
    */
    void retrieveInterface(unsigned long host_id);
    
    /**
    * The function for preprocessing task.
    */
    void prepare();
    /**
    * The function to retrieve the prefix used for tap.
    * @return - Prefix as a string
    */ 
    string tapInterfacePrefix();
    /**
    * Destructor of the class.
    */
    virtual ~KVMWithLibvirt();
};

#endif /* KVMWITHLIBVIRT_H_ */
