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
 * PartitionAnalyzer.cpp
 *
 *  Created on: 2013-08-23
 *      Author: ar3roy
 */

#include "PartitionAnalyzer.h"
#include <float.h>
#include <iostream>
#include <cstring>
#include <map>
#include <string>
#include <list>

using namespace std;

PartitionAnalyzer::PartitionAnalyzer(PhysicalMachines* machine, Mapping* mapping,
		InputTopology* topology) {

	double** bandwidth;
	topology->populateTopologyBandwidth(bandwidth);

	map<string, double> cutEdgeCount;
	map<string, double> cutEdgeBWCount;
	map<string, double> cpuCount;
	map<string, int> machines;
	int counter = 0;
	for(unsigned long i = 0; i < topology->getNumberOfSwitches(); i++)
	{
		if(machines.find(mapping->getMachine(i))== machines.end())
		{
			machines[mapping->getMachine(i)] = 1;
			counter ++;
		}
	}

	cout << "Number of Machines: " << counter << endl;

	for(unsigned long i = 0; i < topology->getNumberOfSwitches(); i++)
	{
		if(cpuCount.find(mapping->getMachine(i)) == cpuCount.end())
			cpuCount[mapping->getMachine(i)] = 1;
		else
			cpuCount[mapping->getMachine(i)]++;
	}
	for(unsigned long i = 0; i < topology->getNumberOfSwitches()-1; i++)
	{
		for(unsigned long j = i+1; j < topology->getNumberOfSwitches(); j++)
		{
			if(bandwidth[i][j] != 0 && mapping->getMachine(i).compare(mapping->getMachine(j)) == 0)
			{
				if(cpuCount.find(mapping->getMachine(i)) == cpuCount.end())
					cpuCount[mapping->getMachine(i)] = bandwidth[i][j]*0.001;
				else
					cpuCount[mapping->getMachine(i)]+=bandwidth[i][j]*0.001;
				/*if(cpuCount.find(mapping->getMachine(j)) == cpuCount.end())
					cpuCount[mapping->getMachine(j)] = bandwidth[i][j]*0.001;
				else
					cpuCount[mapping->getMachine(j)]+=bandwidth[i][j]*0.001;*/
			}
			if(bandwidth[i][j] != 0 && mapping->getMachine(i).compare(mapping->getMachine(j)) != 0)
			{
				if(cutEdgeCount.find(mapping->getMachine(i)) == cutEdgeCount.end())
					cutEdgeCount[mapping->getMachine(i)] = 1;
				else
					cutEdgeCount[mapping->getMachine(i)]++;

				if(cutEdgeBWCount.find(mapping->getMachine(i)) == cutEdgeBWCount.end())
					cutEdgeBWCount[mapping->getMachine(i)] = bandwidth[i][j];
				else
					cutEdgeBWCount[mapping->getMachine(i)] += bandwidth[i][j];

				if(cpuCount.find(mapping->getMachine(i)) == cpuCount.end())
					cpuCount[mapping->getMachine(i)] = bandwidth[i][j]*0.001*2;
				else
					cpuCount[mapping->getMachine(i)] += bandwidth[i][j]*0.001*2;

				if(cutEdgeCount.find(mapping->getMachine(j)) == cutEdgeCount.end())
					cutEdgeCount[mapping->getMachine(j)] = 1;
				else
					cutEdgeCount[mapping->getMachine(j)]++;

				if(cutEdgeBWCount.find(mapping->getMachine(j)) == cutEdgeBWCount.end())
					cutEdgeBWCount[mapping->getMachine(j)] = bandwidth[i][j];
				else
					cutEdgeBWCount[mapping->getMachine(j)] += bandwidth[i][j];

				if(cpuCount.find(mapping->getMachine(j)) == cpuCount.end())
					cpuCount[mapping->getMachine(j)] = bandwidth[i][j]*0.001*2;
				else
					cpuCount[mapping->getMachine(j)] += bandwidth[i][j]*0.001*2;

			}
		}
	}

	for(unsigned long i=0; i < machine->getNumberOfPhysicalMachines(); i++)
	{
		if(cpuCount.find(machine->getIPAddress(i)) != cpuCount.end())
		{
			cpuCount[machine->getIPAddress(i)] /= machine->getCores(i);
		}
		if(cutEdgeBWCount.find(machine->getIPAddress(i)) != cutEdgeBWCount.end())
		{
			cutEdgeBWCount[machine->getIPAddress(i)] /= machine->getBandwidth(i);
		}
	}
	for(map<string, double>::iterator iter = cpuCount.begin(); iter != cpuCount.end(); iter++)
	{
		//iter->second /=  machine->getCores(iter->first);
		cout << iter->first << " " << machine->getCores(iter->first) << endl;

	}

	double sum_cut_edges = 0;
	double sum_bw = 0;
	double sum_cpu = 0;
	double max_cut_edges = -1;
	double max_bw = -1;
	double max_cpu = -1;
	double min_cut_edges = DBL_MAX;
	double min_bw = DBL_MAX;
	double min_cpu = DBL_MAX;

	for(map<string, double>::iterator iter = cpuCount.begin(); iter != cpuCount.end(); iter++)
	{
		sum_cpu += iter->second;
		max_cpu = iter->second>max_cpu?iter->second:max_cpu;
		min_cpu = iter->second<min_cpu?iter->second:min_cpu;
	}
	for(map<string, double>::iterator iter = cutEdgeCount.begin(); iter != cutEdgeCount.end(); iter++)
	{
		sum_cut_edges += iter->second;
		max_cut_edges = iter->second>max_cut_edges?iter->second:max_cut_edges;
		min_cut_edges = iter->second<min_cut_edges?iter->second:min_cut_edges;
	}
	for(map<string, double>::iterator iter = cutEdgeBWCount.begin(); iter != cutEdgeBWCount.end(); iter++)
	{
		sum_bw += iter->second;

		max_bw = iter->second>max_bw?iter->second:max_bw;

		min_bw = iter->second<min_bw?iter->second:min_bw;
	}

	cout << "Cut Edges: Min: " <<  min_cut_edges << " Max: " << max_cut_edges << " Total: " << sum_cut_edges
			<< " Avg: " << sum_cut_edges/counter << endl;
	cout << "Bandwidth: Min: " <<  min_bw*100 << " Max: " << max_bw*100 << " Total: " << sum_bw*100
			<< " Avg: " << (sum_bw/counter)*100 << endl;
	cout << "CPU: Min: " <<  min_cpu*100 << " Max: " << (max_cpu*100>100?100:max_cpu*100)
			<< " Total: "<< (sum_cpu*100>100?100:sum_cpu*100)
			<< " Avg: " << (sum_cpu/counter)*100 << endl;

}

PartitionAnalyzer::~PartitionAnalyzer() {
	// TODO Auto-generated destructor stub
}

