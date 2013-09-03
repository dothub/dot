/*
 * Hosts.cpp
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
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

