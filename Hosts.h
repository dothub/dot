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
 * Hosts.h
 *
 *  Created on: 2013-08-12
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef HOSTS_H_
#define HOSTS_H_

#include <string>
#include <vector>
using namespace std;

class Hosts {
    struct HostAttribute
    {
        unsigned long host_id;
        unsigned long switch_id;
        string mac;
        string ip;
        unsigned int cpu;
        unsigned long interfaceBandwidth;
        string interfaceName;
    };
    static Hosts* hosts;
    Hosts();

    unsigned long numberOfHosts;
    vector<HostAttribute > hostIdVector;

public:
    static Hosts* getHosts();
    void populateHosts(string fileName);

    unsigned long getNumberOfHosts();

    unsigned long getSwitch(unsigned long hostId);
    string getMacAddress(unsigned long hostId);
    string getIPAddress(unsigned long hostId);
    unsigned int getCPU(unsigned long hostId);
    unsigned long getBandwidth(unsigned long hostId);
    string getInterfaceName(unsigned long hostId);
    void setInterfaceName(unsigned long hostId, string name);

    virtual ~Hosts();
};

#endif /* HOSTS_H_ */
