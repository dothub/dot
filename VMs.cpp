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
 * VMs.cpp
 *
 *  Created on: 2013-08-12
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "VMs.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

VMs* VMs::vms = NULL;

VMs::VMs() {

}

VMs* VMs::getVMs() {

    if(vms == NULL)
        vms = new VMs();

    return vms;
}

void VMs::populateVMs(string fileName) {
    ifstream fin(fileName.c_str());

    if(fin.is_open())
    {
        fin >> this->numberOfVMs;


        for(unsigned long i = 0; i < this->numberOfVMs; i++)
        {
            string host_str, switch_str, mac, ip;
            unsigned int cpu;
            unsigned long bandwidth;
            unsigned short memory;
            string image;
            fin >> host_str >> switch_str >> mac >> ip >> cpu >> bandwidth >> memory >> image;

            HostAttribute newHost;
            newHost.host_id = atol(host_str.substr(1).c_str())-1;
            newHost.switch_id = atol(switch_str.substr(1).c_str())-1;
            newHost.mac = mac;
            newHost.ip = ip;
            newHost.cpu = cpu;
            newHost.interfaceBandwidth = bandwidth;
            newHost.memory = memory;
            newHost.image_id = atoi(image.substr(1).c_str())-1;
            newHost.interfaceName = "";

            this->hostIdVector.push_back(newHost);
        }


        fin.close();
    }
    else
        cout << "Unable to open host file: " << fileName << endl;
}
unsigned short VMs::getMemory(unsigned long hostId) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return 0;
    }

    return this->hostIdVector[hostId].memory;

}

unsigned int VMs::getImageId(unsigned long hostId) {
 
    if(hostId < 0 || hostId >= this->hostIdVector.size())
    { 
        cout << "Invalid Host ID " << hostId << endl;
        return 0; 
    }
 
    return this->hostIdVector[hostId].image_id; 
 
}


unsigned long VMs::getSwitch(unsigned long hostId) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return -1;
    }

    return this->hostIdVector[hostId].switch_id;
}

string VMs::getMacAddress(unsigned long hostId) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return "None";
    }

    return this->hostIdVector[hostId].mac;
}

string VMs::getIPAddress(unsigned long hostId) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return "None";
    }

    return this->hostIdVector[hostId].ip;

}

unsigned int VMs::getCPU(unsigned long hostId) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return 0;
    }

    return this->hostIdVector[hostId].cpu;

}

unsigned long VMs::getBandwidth(unsigned long hostId) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return 0;
    }

    return this->hostIdVector[hostId].interfaceBandwidth;

}


void VMs::setInterfaceName(unsigned long hostId, string name) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return;
    }

    this->hostIdVector[hostId].interfaceName = name;

}


string VMs::getInterfaceName(unsigned long hostId) {

    if(hostId < 0 || hostId >= this->hostIdVector.size())
    {
        cout << "Invalid Host ID " << hostId << endl;
        return "Error";
    }

    return this->hostIdVector[hostId].interfaceName;

}


unsigned long VMs::getNumberOfVMs() {

    return this->numberOfVMs;
}

VMs::~VMs() {

}

