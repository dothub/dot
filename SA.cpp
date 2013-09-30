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
 * SimulatedAnnealing.cpp
 *
 *  Created on: 2013-03-18
 *      Author: ar3roy
 */
#include <time.h>
#include <stdlib.h>
#include "SA.h"
#include <string.h>
#include <math.h>
#include <float.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Util.h"
using namespace std;


SA::SA(string SAConfigurationFile, InputTopology* inputTopology, PhysicalMachines* physicalMachines, Mapping* mapping)
{

	//initialzing the random number generator
	seed();
	
	this->mapping = mapping;
	this->physicalMachines = physicalMachines;

	this->processConfigurationFile(SAConfigurationFile);

	this->numberOfPhysicalMachines = this->physicalMachines->getNumberOfPhysicalMachines();
	this->numberOfSwitches = inputTopology->getNumberOfSwitches();
	cout << this->numberOfSwitches;

	inputTopology->populateTopologyBandwidth(this->logical_topology);

	
}

SA::~SA()
{
	delete[] this->stepProbabilities;
	delete [] this->accumulatedStepProbabilities;

	for(unsigned long i = 0; i < this->numberOfSwitches; i++)
	{
		delete[]this->logical_topology[i];
	}

	delete [] this->logical_topology;

	delete [] this->globalBest;
}

void SA::run()
{
	this->globalBest = new long [this->numberOfSwitches];
	long * current;
	generateInitalState(current);
	memcpy(this->globalBest, current, this->numberOfSwitches*sizeof(long));
	this->globalBestCost = cost(this->globalBest);

	int runCount = 0;
	while(runCount ++ < this->numberOfTrials)
	{
		long * outcomeOfSingleRun;

		simRun(current, outcomeOfSingleRun);

		double singleRunCost = cost(outcomeOfSingleRun);

		if(singleRunCost < this->globalBestCost)
		{
			this->globalBestCost = singleRunCost;
			memcpy(this->globalBest, outcomeOfSingleRun, this->numberOfSwitches*sizeof(long));
		}

		delete [] outcomeOfSingleRun;
		delete [] current;
		generateInitalState(current);
	}

	generateOutput();
}

void SA::generateOutput()
{
	cout << "output assignment" << endl;
	for(unsigned long i = 0; i < this->numberOfSwitches; i++)
	{
		this->instertMapping(this->mapping, this->physicalMachines->getIPAddress(this->globalBest[i]));
	}

}
//processing input files
void SA::processConfigurationFile(string fileName)
{
	this->alpha = 1;
	this->beta = 1;
	this->gamma = 1000;
	this->initalTemperature = 100;
	this->reductionRate = 0.95;
	this->minimumTemp = 0.01;
	this->numberOfSteps = 100;
	this->numberOfTrials = 5;

	this->typesOfSteps = 2;
	this->stepProbabilities = new double[this->typesOfSteps];

	stepProbabilities[0] = 0.6;
	stepProbabilities[1] = 0.4;

	map<string, string> eachConfiguration;

	ifstream fin(fileName.c_str());

	if(fin.is_open())
	{
		while(!fin.eof())
		{
			string line, key, value;
			fin >> line;
			Util::parseKeyValue(line, key, value, '=');

			if(key.compare(""))
			{
				//cout << key << endl << value << endl;
				eachConfiguration[key] = value;
			}
		}

		fin.close();
	}
	else
		cout << "Unable to open SA configuration file: " << fileName <<  endl;

	//Getting the values
	if(eachConfiguration.find("alpha") != eachConfiguration.end())
		alpha = atof(eachConfiguration["alpha"].c_str());

	if(eachConfiguration.find("beta") != eachConfiguration.end())
		beta = atof(eachConfiguration["beta"].c_str());

	if(eachConfiguration.find("gamma") != eachConfiguration.end())
		gamma = atof(eachConfiguration["gamma"].c_str());

	if(eachConfiguration.find("initalTemperature") != eachConfiguration.end())
		initalTemperature = atof(eachConfiguration["initalTemperature"].c_str());

	if(eachConfiguration.find("reductionRate") != eachConfiguration.end())
		reductionRate = atof(eachConfiguration["reductionRate"].c_str());

	if(eachConfiguration.find("minimumTemperature") != eachConfiguration.end())
		minimumTemp = atof(eachConfiguration["minimumTemperature"].c_str());

	if(eachConfiguration.find("numberOfSteps") != eachConfiguration.end())
		numberOfSteps = atoi(eachConfiguration["numberOfSteps"].c_str());

	if(eachConfiguration.find("numberOfTrials") != eachConfiguration.end())
		numberOfTrials = atoi(eachConfiguration["numberOfTrials"].c_str());

	if(eachConfiguration.find("typesOfSteps") != eachConfiguration.end())
		typesOfSteps = atoi(eachConfiguration["typesOfSteps"].c_str());


	if(eachConfiguration.find("stepProbabilities") != eachConfiguration.end())
	{
		string stepProbabilitiesString = eachConfiguration["stepProbabilities"];
		vector<string>* probabilities;

		Util::parseString(stepProbabilitiesString, probabilities, ',');

		delete [] stepProbabilities;
		stepProbabilities = new double[typesOfSteps];

		for(int i = 0; i < typesOfSteps; i++)
			stepProbabilities[i] = atof(probabilities->at(i).c_str());
	}



	for(short i = 1; i < this->typesOfSteps; i++)
		this->stepProbabilities[i]+=this->stepProbabilities[i-1];

	//generating the accumulated step probabilities
	this->accumulatedStepProbabilities = new long[this->typesOfSteps];
	for(short i = 0; i < this->typesOfSteps; i++)
	{
		this->accumulatedStepProbabilities[i] = (long)((this->stepProbabilities[i]/this->stepProbabilities[this->typesOfSteps-1])
				* 100);
	}

}


void SA::generateInitalState(long *& next)
{
	next = new long[this->numberOfSwitches];
	for (unsigned long i = 0; i < this->numberOfSwitches; i++)
	{
		long physicalMachine = unifRand(this->numberOfPhysicalMachines)-1;
		next[i] = physicalMachine;
	}
}



void SA::printCost(long * next)
{
	
}
double SA::cost(long * next)
{

	long edgeCount = 0;
	double bandwidth = 0;

	for(unsigned long i = 0; i < this->numberOfSwitches-1; i++)
	{
		for(unsigned long j = i+1; j < this->numberOfSwitches; j++)
		{
			if(next[i] != next[j])
			{
				edgeCount ++;
				//both way bandwidth
				bandwidth += this->logical_topology[i][j];
				bandwidth += this->logical_topology[j][i];
			}
		}
	}
	long * hostedVirtualInstances = new long[this->numberOfPhysicalMachines];
	memset(hostedVirtualInstances, 0, this->numberOfPhysicalMachines*sizeof(long));
	
	for(unsigned long i = 0; i < this->numberOfSwitches; i++)
	{
		hostedVirtualInstances[next[i]]++;
	}
	//calcualting sample standard deviation
	long sum = 0;
	for(long i = 0; i < this->numberOfPhysicalMachines; i++)
	{
		sum += hostedVirtualInstances[i];
	}

	double differenceSquare = 0;
	for(long i = 0; i < this->numberOfPhysicalMachines; i++)
	{
		differenceSquare += pow(hostedVirtualInstances[i]-sum/((double)this->numberOfPhysicalMachines), 2);
	}
	double standardDeviationCost = sqrt(differenceSquare/this->numberOfPhysicalMachines);

	delete[] hostedVirtualInstances;

	return this->alpha*edgeCount + this->beta*bandwidth + this->gamma*standardDeviationCost;
}


void SA::successor(long* current, long * &next)
{
	
	short randomNumber = unifRand(100);

	next = new long[this->numberOfSwitches];
	memcpy(next, current, this->numberOfSwitches*sizeof(long));

	if(randomNumber <= this->accumulatedStepProbabilities[0])
	{
		//Swap
		long switch1 = unifRand(this->numberOfSwitches)-1;
		long switch2 = unifRand(this->numberOfSwitches)-1;

		//swap the switches
		next[switch1] = current[switch2];
		next[switch2] = current[switch1];
	}
	else
	{
		//move
		long switchToChange = unifRand(this->numberOfSwitches)-1;
		long destiantionPhysicalMachine = unifRand(this->numberOfPhysicalMachines)-1;
		next[switchToChange] = destiantionPhysicalMachine;
	}
}


void SA::simRun(long * start, long *&final)
{
	cout << "SA Started" << endl;

	long * current = new long[this->numberOfSwitches];
	memcpy(current, start, this->numberOfSwitches*sizeof(long));

	long * pathBest = 	new long[this->numberOfSwitches];
	memcpy(pathBest, start, this->numberOfSwitches*sizeof(long));

	int stepCount = 0;
	double currentTemperature = this->initalTemperature;

	double currentCost = cost(start);
	double pathBestCost = cost(pathBest);

	while(stepCount++ < this->numberOfSteps)
	{
		long * next;
		successor(current, next);

		double nextCost = cost(next);
		if(nextCost < currentCost)
		{
			currentCost = nextCost;
			delete[] current;
			current = next;

			if(currentCost < pathBestCost)
			{
				pathBestCost = currentCost;
				memcpy(pathBest, current, this->numberOfSwitches*sizeof(long));
			}

		}
		else
		{
			float randomNumber = unifRand();

			float probabilityOfTake = exp((currentCost-nextCost)/currentTemperature);

			if(randomNumber < probabilityOfTake)
			{
				//cout << "worse taken" << endl;

				currentCost = nextCost;
				delete[] current;
				current = next;
			}
		}
		currentTemperature = this->reductionRate * currentTemperature;
	}

	final = pathBest;
}

//
// Generate a random number between 0 and 1
// return a uniform number in [0,1].
double SA::unifRand()
{
    return rand() / double(RAND_MAX);
	//return distribution(generator);
}
//
// Generate a random number in a real interval.
// param a one end point of the interval
// param b the other end of the interval
// return a inform rand numberin [a,b].
double SA::unifRand(double a, double b)
{
    return (b-a)*unifRand() + a;
}
//
// Generate a random integer between 1 and a given value.
// param n the largest value
// return a uniform random value in [1,...,n]
long SA::unifRand(long n)
{

    if (n < 0) n = -n;
    if (n==0) return 0;
    /* There is a slight error in that this code can produce a return value of n+1
    **
    **  return long(unifRand()*n) + 1;
    */
    //Fixed code
    long guard = (long) (unifRand() * n) +1;
    return (guard > n)? n : guard;
}
//
// Reset the random number generator with the system clock.
void SA::seed()
{
    srand(time(0));
}
