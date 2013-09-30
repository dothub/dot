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
 * SimulatedAnnealing.h
 *
 *  Created on: 2013-03-18
 *      Author: ar3roy
 */

#ifndef SA_H
#define SA_H
#include "PartitioningAlgorithm.h"
#include "PhysicalMachines.h"
#include "InputTopology.h"
#include "Mapping.h"

#include <string>


using namespace std;

class SA : public PartitioningAlgorithm{
	//inputs

	double alpha;
	double beta;
	double gamma;

	//sa parameters
	double initalTemperature;
	double reductionRate;
	double minimumTemp;
	int numberOfSteps;
	int numberOfTrials;
	int typesOfSteps;
	double * stepProbabilities;
	long * accumulatedStepProbabilities;

	double **logical_topology;//stores the logical topology in adjacency matrix

	unsigned long numberOfSwitches;
	unsigned int numberOfPhysicalMachines;

	
	void simRun(long * start, long *&final);
	
	long * globalBest;
	double globalBestCost;
	double cost(long * next);
	void printCost(long * next);



	//step generation functions
	void generateInitalState(long * &next);
	void successor(long* current, long * &next);
	void generateOutput();

	//Random number generator
	double unifRand();
	double unifRand(double a, double b);
	long unifRand(long n);
	void seed();


	//process input
	void processConfigurationFile(string fileName);

	Mapping* mapping;
	PhysicalMachines* physicalMachines;

public:
	void run();
	SA(string SAConfigurationFile, InputTopology * inputTopology, PhysicalMachines* physicalMachines, Mapping * mapping);
	~SA();
};

#endif /* SA_H */
