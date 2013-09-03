/*
 * PhysicalMachines.cpp
 *
 *  Created on: 2013-08-07
 *      Author: ar3roy
 */

#include "PhysicalMachines.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

PhysicalMachines* PhysicalMachines::physicalMachines = NULL;

PhysicalMachines* PhysicalMachines:: getPhysicalMachines()
{
	if(physicalMachines == NULL)
		physicalMachines = new PhysicalMachines();

	return physicalMachines;
}


PhysicalMachines::PhysicalMachines() {


}

string PhysicalMachines::getName(unsigned int machineId) {

	if(machineId < 0 || machineId >= this->physicalMachineIdVector.size())
	{
		cout << "Invalid Machine ID " << machineId << endl;
		return "None";
	}

	return this->physicalMachineIdVector[machineId].name;
}

string PhysicalMachines::getName(string machineIP) {

	if(this->physicalMachineIPMap.count(machineIP) == 0)
	{
		cout << "No machine found with the IP: " << machineIP << endl;
		return "None";
	}


	return this->physicalMachineIPMap[machineIP].name;
}
string PhysicalMachines::getIPAddress(unsigned int machineId) {

	if(machineId < 0 || machineId >= this->physicalMachineIdVector.size())
	{
		cout << "Invalid Machine ID " << machineId << endl;
		return "None";
	}


	return this->physicalMachineIdVector[machineId].ip;
}

unsigned int PhysicalMachines::getCores(unsigned int machineId) {

if(machineId < 0 || machineId >= this->physicalMachineIdVector.size())
	{
		cout << "Invalid Machine ID " << machineId << endl;
		return 0;
	}


	return this->physicalMachineIdVector[machineId].cores;
}

unsigned int PhysicalMachines::getCores(string machineIP) {

	if(this->physicalMachineIPMap.count(machineIP) == 0)
	{
		cout << "No machine found with the IP: " << machineIP << endl;
		return 0;
	}


	return this->physicalMachineIPMap[machineIP].cores;
}

unsigned int PhysicalMachines::getDisk(unsigned int machineId) {

	if(machineId < 0 || machineId >= this->physicalMachineIdVector.size())
	{
		cout << "Invalid Machine ID " << machineId << endl;
		return 0;
	}


	return this->physicalMachineIdVector[machineId].disk;
}

unsigned int PhysicalMachines::getDisk(string machineIP) {

	if(this->physicalMachineIPMap.count(machineIP) == 0)
	{
		cout << "No machine found with the IP: " << machineIP << endl;
		return 0;
	}


	return this->physicalMachineIPMap[machineIP].disk;
}

unsigned int PhysicalMachines::getMemory(unsigned int machineId) {

	if(machineId < 0 || machineId >= this->physicalMachineIdVector.size())
	{
		cout << "Invalid Machine ID " << machineId << endl;
		return 0;
	}


	return this->physicalMachineIdVector[machineId].memory;
}

unsigned int PhysicalMachines::getMemory(string machineIP) {

	if(this->physicalMachineIPMap.count(machineIP) == 0)
	{
		cout << "No machine found with the IP: " << machineIP << endl;
		return 0;
	}


	return this->physicalMachineIPMap[machineIP].memory;
}

string PhysicalMachines::getExternalInterface(unsigned int machineId) {

	if(machineId < 0 || machineId >= this->physicalMachineIdVector.size())
	{
		cout << "Invalid Machine ID " << machineId << endl;
		return "None";
	}

	return this->physicalMachineIdVector[machineId].interface;
}

string PhysicalMachines::getExternalInterface(string machineIP) {

	if(this->physicalMachineIPMap.count(machineIP) == 0)
	{
		cout << "No machine found with the IP: " << machineIP << endl;
		return "None";
	}
	return this->physicalMachineIPMap[machineIP].interface;
}

unsigned int PhysicalMachines::getNumberOfPhysicalMachines() {

	return this->numberOfPhysicalMachines;
}

void PhysicalMachines::populateMachines(string fileName) {

	ifstream fin(fileName.c_str());

	if(fin.is_open())
	{
		fin >> this->numberOfPhysicalMachines;


		for(unsigned int i = 0; i < this->numberOfPhysicalMachines; i++)
		{
			string name, ip, cores, disk, memory, interface;
			double bandwidth;
			fin >> name >> ip >> cores >> disk >> memory >> interface >> bandwidth;

			MachineAttribute newMachine;
			newMachine.name = name;
			newMachine.ip = ip;
			newMachine.cores = atoi(cores.c_str());
			newMachine.disk = atoi(disk.c_str());
			newMachine.memory = atoi(memory.c_str());
			newMachine.interface = interface;
			newMachine.bandwidth = bandwidth;

			this->physicalMachineIdVector.push_back(newMachine);
			this->physicalMachineIPMap[ip] = newMachine;
			this->physicalMachineNameMap[name] = newMachine;
		}


		fin.close();
	}
	else
		cout << "Unable to open physical machine file: " << fileName << endl;
}
void PhysicalMachines::populateDelay(string fileName) {

	ifstream fin(fileName.c_str());

	if(fin.is_open())
	{
		unsigned long numberOfPairs;
		fin>>numberOfPairs;
		for(unsigned long i = 0; i < numberOfPairs; i++)
		{
			string machine1, machine2;
			double delay;
			fin >> machine1 >> machine2 >> delay;
			string ipMachine1 = this->physicalMachineNameMap[machine1].ip;
			string ipMachine2 = this->physicalMachineNameMap[machine2].ip;

			this->physicalDelays[make_pair(ipMachine1, ipMachine2)] = delay;
			this->physicalDelays[make_pair(ipMachine2, ipMachine1)] = delay;
		}


		fin.close();

	}
	else
		cout << "Unable to open physical machine delay file: " << fileName << endl;
}


double PhysicalMachines::getDelay(string machine1_IP, string machine2_IP) {

	if(this->physicalDelays.find(make_pair(machine1_IP, machine2_IP)) != this->physicalDelays.end())
	{
		return this->physicalDelays[make_pair(machine1_IP, machine2_IP)];
	}
	return 0;
}

double PhysicalMachines::getDelay(unsigned int machine1_Id,
		unsigned int machine2_Id) {
	string ipMachine1 = this->physicalMachineIdVector[machine1_Id].ip;
	string ipMachine2 = this->physicalMachineIdVector[machine2_Id].ip;

	if(this->physicalDelays.find(make_pair(ipMachine1, ipMachine2)) != this->physicalDelays.end())
	{
		return this->physicalDelays[make_pair(ipMachine1, ipMachine2)];
	}
	return 0;
}

double PhysicalMachines::getBandwidth(unsigned int machineId) {
	if(machineId < 0 || machineId >= this->physicalMachineIdVector.size())
	{
		cout << "Invalid Machine ID " << machineId << endl;
		return 0;
	}


	return this->physicalMachineIdVector[machineId].bandwidth;
}

double PhysicalMachines::getBandwidth(string machineIP) {
	if(this->physicalMachineIPMap.count(machineIP) == 0)
	{
		cout << "No machine found with the IP: " << machineIP << endl;
		return 0;
	}
	return this->physicalMachineIPMap[machineIP].bandwidth;
}

PhysicalMachines::~PhysicalMachines() {

}

