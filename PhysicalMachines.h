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
 * PhysicalMachines.h
 *
 *  Created on: 2013-08-07
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef PHYSICALMACHINES_H_
#define PHYSICALMACHINES_H_

#include <string>
#include <map>
#include <vector>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

using namespace std;

/**
* This singleton class stores all controller inforamtion.
*/
class PhysicalMachines {

    LoggerPtr* selfLogger;
    
     /**
    * This structure stores name, ip, cores, disk, memory, interface name and bandwidth of a machine.
    */
    struct MachineAttribute
    {
        string name;
        string ip;
        unsigned int cores;
        unsigned int disk;
        unsigned int memory;
        string interface;
        double bandwidth;

    };

    PhysicalMachines();

    static PhysicalMachines* physicalMachines;

    unsigned int numberOfPhysicalMachines;

    vector<MachineAttribute > physicalMachineIdVector;
    map<string, MachineAttribute > physicalMachineIPMap;
    map<string, MachineAttribute > physicalMachineNameMap;
    map<pair<string, string>, double > physicalDelays;

public:
    
    static PhysicalMachines* getPhysicalMachines();

    unsigned int getNumberOfPhysicalMachines();
    
    /**
    * This function returns the machine name from machine id
    * @param - machineId 
    * @return - Machine name as a string
    */
    string getName(unsigned int machineId);
    
     /**
    * This function returns the machine name from machine IP Address
    * @param - machineIP
    * @return - Machine name as a string
    */
    string getName(string machineIP);
    
    /**
    * This function returns the machine IP from machine id
    * @param - machineId 
    * @return - Machine IP Address as a string
    */
    string getIPAddress(unsigned int machineId);
    
    /**
    * This function returns the number of cores from machine id
    * @param - machineId 
    * @return - Number of cores
    */
    unsigned int getCores(unsigned int machineId);
    
    /**
    * This function returns the number of cores from from machine IP
    * @param - machineIP
    * @return - Number of cores
    */
    unsigned int getCores(string machineIP);
    
    /**
    * This function returns the disk from from machine ID
    * @param - machineID
    * @return - disks
    */
    unsigned int getDisk(unsigned int machineId);
    
    /**
    * This function returns the disk from from machine IP
    * @param - machineIP
    * @return - disks
    */
    unsigned int getDisk(string machineIP);
    
    /**
    * This function returns the memory from from machine ID
    * @param - machineID
    * @return - memory
    */

    unsigned int getMemory(unsigned int machineId);
    
    /**
    * This function returns the disk from from machine IP
    * @param - machineIP
    * @return - memory
    */

    unsigned int getMemory(string machineIP);
    
     /**
     * This function returns the interface bandwidth from from machine ID
    * @param - machineID
    * @return - bandwidth
    */

    double getBandwidth(unsigned int machineId);
    /**
     * This function returns the interface bandwidth from from machine IP
    * @param - machineIP
    * @return - bandwidth
    */

    double getBandwidth(string machineIP);
    /**
     * This function returns the interface name from from machine ID
    * @param - machineID
    * @return - interface name
    */
    string getExternalInterface(unsigned int machineId);
    /**
     * This function returns the interface name from from machine IP
    * @param - machineIP
    * @return - interface name
    */
    string getExternalInterface(string machineIP);
    /**
     * This function returns the delay between two machines
    * @param - IP address of machine 1
    * @param - IP address of machine 2 
    * @return - delay (ms)
    */    
    double getDelay(string machine1_IP, string machine2_IP);
    /**
    * This function returns the delay between two machines
    * @param - ID of machine 1
    * @param - ID of machine 2 
    * @return - delay (ms)
    */
    double getDelay(unsigned int machine1_Id, unsigned int machine2_Id);

    /**
    * The function to populate machines from a file.
    * @param fileName - Name of the file
    */
    void populateMachines(string fileName);
    /**
    * The function to populate pairwise delay between machinesr from a file.
    * @param fileName - Name of the file
    */
    void populateDelay(string fileName);
    /**
    * Destructor of the class.
    */
    virtual ~PhysicalMachines();
};

#endif /* PHYSICALMACHINES_H_ */
