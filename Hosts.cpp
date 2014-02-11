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
 * Hosts.cpp
 *
 *  Created on: 2013-08-12
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "Hosts.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

Hosts* Hosts::hosts = NULL;

Hosts::Hosts() {

}

Hosts* Hosts::getHosts() {

    if(hosts == NULL)
        hosts = new Hosts();

    return hosts;
}

void Hosts::populateHosts(string fileName) {
    ifstream fin(fileName.c_str());

    if(fin.is_open())
    {
        fin >> this->numberOfHosts;


        for(unsigned long i = 0; i < this->numberOfHosts; i++)
        {
            string host_str, switch_str, mac, ip;
            unsigned int cpu;
            fin >> host_str >> switch_str >> mac >> ip >> cpu;

            HostAttribute newHost;
            newHost.host_id = atol(host_str.substr(1).c_str())-1;
            newHost.switch_id = atol(switch_str.substr(1).c_str())-1;
            newHost.mac = mac;
            newHost.ip = ip;
            newHost.cpu = cpu;

            this->hostIdVector.push_back(newHost);

        }


        fin.close();
    }
    else
        cout << "Unable to open host file: " << fileName << endl;
}

unsigned long Hosts::getSwitch(unsigned long hostId) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return -1;
    }

    return this->hostIdVector[hostId].switch_id;
}

string Hosts::getMacAddress(unsigned long hostId) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return "None";
    }

    return this->hostIdVector[hostId].mac;
}

string Hosts::getIPAddress(unsigned long hostId) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return "None";
    }

    return this->hostIdVector[hostId].ip;

}

unsigned int Hosts::getCPU(unsigned long hostId) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return 0;
    }

    return this->hostIdVector[hostId].cpu;

}

unsigned long Hosts::getNumberOfHosts() {

    return this->numberOfHosts;
}

Hosts::~Hosts() {

}

