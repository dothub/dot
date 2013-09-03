/*
 * SimulatedAnnealing.h
 *
 *  Created on: 2013-03-18
 *      Author: ar3roy
 */

#ifndef SA_WEIGHTED_H
#define SA_WEIGHTED_H
#include "PartitioningAlgorithm.h"
#include "PhysicalMachines.h"
#include "InputTopology.h"
#include "Mapping.h"
#include "Hosts.h"

#include <string>


using namespace std;

class Mapping;

class SA_Weighted : public PartitioningAlgorithm{
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
	unsigned long numberOfHosts;
	unsigned int* cpuOfPhysicalMachines;

	
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
	Hosts* hosts;

public:
	void run();
	SA_Weighted(string SAConfigurationFile, InputTopology * inputTopology, PhysicalMachines* physicalMachines, Mapping * mapping, Hosts* hosts);
	~SA_Weighted();
};

#endif /* SA_WEIGHTED_H */
