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
 *      Author: ar3roy
 */

#ifndef PHYSICALMACHINES_H_
#define PHYSICALMACHINES_H_

#include <string>
#include <map>
#include <vector>

using namespace std;

class PhysicalMachines {

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
	string getName(unsigned int machineId);
	string getName(string machineIP);
	string getIPAddress(unsigned int machineId);
	unsigned int getCores(unsigned int machineId);
	unsigned int getCores(string machineIP);
	unsigned int getDisk(unsigned int machineId);
	unsigned int getDisk(string machineIP);
	unsigned int getMemory(unsigned int machineId);
	unsigned int getMemory(string machineIP);
	double getBandwidth(unsigned int machineId);
	double getBandwidth(string machineIP);
	string getExternalInterface(unsigned int machineId);
	string getExternalInterface(string machineIP);
	double getDelay(string machine1_IP, string machine2_IP);
	double getDelay(unsigned int machine1_Id, unsigned int machine2_Id);

	void populateMachines(string fileName);
	void populateDelay(string fileName);

	virtual ~PhysicalMachines();
};

#endif /* PHYSICALMACHINES_H_ */
