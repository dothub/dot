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
 * GuranteedEmbedding.cpp
 *
 *  Created on: 2013-08-31
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "GuranteedEmbedding.h"
#include <string.h>
#include <math.h>
#include <float.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "Util.h"
using namespace std;


GuranteedEmbedding::GuranteedEmbedding(string configurationFile, InputTopology* inputTopology, PhysicalMachines* physicalMachines, Mapping* mapping, Hosts* hosts)
{

    //initialzing the random number generator
    seed();

    cout << "Guranted started" << endl;

    this->mapping = mapping;
    this->physicalMachines = physicalMachines;
    this->hosts = hosts;
    this->processConfigurationFile(configurationFile);


    this->numberOfHosts = this->hosts->getNumberOfHosts();

    processPhysicalMachines();
    //cout << "After process Machine" << endl;
    processInputTopology(inputTopology);


    //cout << "Befor greedy started" << endl;
    //cout << "Map size: " << this->unassignedNode.size()<< endl;


}

bool GuranteedEmbedding::generateGreedy()
{
    cout << "At GG NS: " << this->numberOfSwitches << endl;
    for(unsigned long count = 0; count < this->numberOfSwitches; count++)
    {
        cout << "Calling best node" << endl;
        unsigned long switch_id = this->getBestNode();
        cout << "SwithchId: " << switch_id << endl;
        unsigned int machine_id = this->getBestPhysicalMachine(switch_id);
        cout << machine_id << endl;
        if(machine_id == -1)
        {
            cout << "No feasible mapping" << endl;
            return false;
        }
        //updated the feasiblity
        for(unsigned long i = 0; i < this->numberOfSwitches; i++)
        {
            if(this->logical_topology[switch_id][i] != 0)
            {
                //not embedded neighbor
                for(list<unsigned int>::iterator iterator = this->unassignedNode[i]->feasibleHosts.begin();
                            iterator != this->unassignedNode[i]->feasibleHosts.end(); iterator++)
                {
                    this->unassignedNode[i]->embeddedNeighbors++;
                    if(this->logical_topology_delay[switch_id][i] < this->physicalMachines->getDelay(machine_id, *iterator))
                    {
                         cout << " removing " << i << " from " << *iterator << endl;
                         iterator = this->unassignedNode[i]->feasibleHosts.erase(iterator);
                    }
                }

            }
        }
        this->assignSwitch(switch_id, machine_id);
        cout << "Assinging to embedding " << endl;
        this->currentEmbedding[switch_id] = machine_id;
    }
    return true;
}
unsigned long GuranteedEmbedding::getNeighborCount(unsigned int switchId)
{
    unsigned long count = 0;
    for(unsigned int i = 0; i < this->numberOfSwitches; i++)
    {
        if(this->logical_topology[switchId][i]!= 0)
            count ++;
    }
    return count;
}

double GuranteedEmbedding::getAggregatedBandwidths(unsigned int switchId)
{
    double totalBandwdith = 0;
    for(unsigned int i = 0; i < this->numberOfSwitches; i++)
    {
        totalBandwdith += this->logical_topology[switchId][i];

    }
    return totalBandwdith;
}
void GuranteedEmbedding::processPhysicalMachines()
{
    this->numberOfPhysicalMachines = this->physicalMachines->getNumberOfPhysicalMachines();
    this->cpuOfPhysicalMachines = new unsigned int[this->numberOfPhysicalMachines];

    for(unsigned int i = 0; i < this->numberOfPhysicalMachines; i++)
    {
        this->cpuOfPhysicalMachines[i] = this->physicalMachines->getCores(i);

        PhysicalMachineValue* newValue = new PhysicalMachineValue;
        newValue->totalCPU = this->physicalMachines->getCores(i);
        newValue->active = false;
        newValue->totalBandwidth = this->physicalMachines->getBandwidth(i);
        newValue->cpuForSwitches = 0;
        newValue->cpuForGateways = 0;
        newValue->bandwdithAllocated = 0;

        this->machines.push_back(newValue);
    }


}

unsigned int GuranteedEmbedding::getBestPhysicalMachine(unsigned long switchId)
{
    //search all feasible
    map<unsigned int, pair<double,double> > physicalMachinesAttributes;
    double minCapacityFactor = DBL_MAX;
    double maxNeighborFactor = -1;

    for(list<unsigned int>::iterator iter = this->unassignedNode[switchId]->feasibleHosts.begin();
            iter != this->unassignedNode[switchId]->feasibleHosts.end(); iter++)
    {
        if(this->machines[*iter]->active == false)
            continue;

        double capacityFactor;
        double neighborFactor;
        getFeasibleValue(switchId, *iter, capacityFactor, neighborFactor);
        cout << *iter << ": capacity " << capacityFactor << " " << neighborFactor <<endl;
        if(capacityFactor < 0)
            continue;

        if(capacityFactor < minCapacityFactor)
            minCapacityFactor = capacityFactor;
        if(neighborFactor > maxNeighborFactor)
            maxNeighborFactor = neighborFactor;

        physicalMachinesAttributes[*iter] = make_pair(capacityFactor, neighborFactor);
    }
    if(physicalMachinesAttributes.size() != 0)
    {
        double maxValue;
        unsigned int bestNode;
        for(map<unsigned int, pair<double,double> >::iterator iter = physicalMachinesAttributes.begin();
                    iter != physicalMachinesAttributes.end(); iter++)
        {
            if(iter == physicalMachinesAttributes.begin())
            {
                bestNode = iter->first;
                maxValue = minCapacityFactor/this->lambda1*iter->second.first
                        +this->lambda2*iter->second.second/maxNeighborFactor;
            }
            else
            {
                double selfFactor = minCapacityFactor/this->lambda1*iter->second.first
                        +this->lambda2*iter->second.second/maxNeighborFactor;
                if(selfFactor > maxValue)
                    bestNode = iter->first;
            }
        }

        return bestNode;
    }
    else
    {

        double capacity = -1;
        int currentBest = -1;
        cout << "Feasible hosts size: " << this->unassignedNode[switchId]->feasibleHosts.size() << endl;

        for(list<unsigned int>::iterator iter = this->unassignedNode[switchId]->feasibleHosts.begin();
                iter != this->unassignedNode[switchId]->feasibleHosts.end(); iter++)
        {
            cout << "feasible host " << *iter << endl;

            if(this->machines[*iter]->active == false && this->machines[*iter]->totalCPU > capacity)
            {
                currentBest = *iter;
                capacity  = this->machines[*iter]->totalCPU;
            }
        }

        //No feasible mapping
        if(currentBest == -1)
            return -1;

        this->machines[currentBest]->active = true;
        cout << "adding " << currentBest << endl;
        return currentBest;

    }
}
void GuranteedEmbedding::assignSwitch(unsigned long switch_id, unsigned int physicalMachine)
{
    double switchCapacity = this->unassignedNode[switch_id]->totalCPU;
    double switchBandwidth = this->unassignedNode[switch_id]->totalBandwidth;

    double repaidBandwidth = 0;
    double neighborEmbedded = 0;

    for(unsigned long i = 0; i < this->numberOfSwitches; i++)
    {
      if(this->logical_topology[switch_id][i] != 0)
      {

          for(list<unsigned long>::iterator iter = this->machines[physicalMachine]->embeddedSwitches.begin();
                  iter != this->machines[physicalMachine]->embeddedSwitches.end(); iter++)
          {
              //if i is embedded in the machine
              if(*iter == i)
              {
                  repaidBandwidth += this->logical_topology[switch_id][i];
                  neighborEmbedded ++;
              }
          }
      }
    }
    this->machines[physicalMachine]->cpuForSwitches += switchCapacity;
    this->machines[physicalMachine]->bandwdithAllocated += (switchBandwidth - repaidBandwidth);
    this->machines[physicalMachine]->cpuForGateways += ((switchBandwidth-repaidBandwidth)*this->rho*2);
    this->machines[physicalMachine]->embeddedSwitches.push_back(switch_id);

}
void GuranteedEmbedding::getFeasibleValue(unsigned long switch_id,
        unsigned int physicalMachine, double &capacityFactor, double& neighborFactor)
{

    double switchCapacity = this->unassignedNode[switch_id]->totalCPU;
    double switchBandwidth = this->unassignedNode[switch_id]->totalBandwidth;

    cout << endl << "SW" << switchCapacity << " " << switchBandwidth << endl;

    double remainingCapacity = this->machines[physicalMachine]->totalCPU
            -this->machines[physicalMachine]->cpuForGateways
            - this->machines[physicalMachine]->cpuForSwitches;
    double remainingBandwidth = this->machines[physicalMachine]->totalBandwidth
            -this->machines[physicalMachine]->bandwdithAllocated;

    cout << "machinecap:" << physicalMachine << " " << remainingCapacity << " " << remainingBandwidth << endl;
    double repaidBandwidth = 0;
    double neighborEmbedded = 0;

    for(unsigned long i = 0; i < this->numberOfSwitches; i++)
    {
      if(this->logical_topology[switch_id][i] != 0)
      {

          for(list<unsigned long>::iterator iter = this->machines[physicalMachine]->embeddedSwitches.begin();
                  iter != this->machines[physicalMachine]->embeddedSwitches.end(); iter++)
          {
              //if i is embedded in the machine
              if(*iter == i)
              {
                  repaidBandwidth += this->logical_topology[switch_id][i];
                  neighborEmbedded ++;
              }
          }
      }
    }

    if((switchBandwidth - repaidBandwidth) > remainingBandwidth)
    {
        capacityFactor = -1;
        neighborFactor = -1;
    }
    else
    {
        capacityFactor = remainingCapacity - switchCapacity + (repaidBandwidth-switchBandwidth)*this->rho*2;
        neighborFactor = neighborEmbedded;
    }

}
void GuranteedEmbedding::updateNeighborsEmbeddedCount(unsigned long switchId)
{
    for(unsigned long i = 0; i < this->numberOfSwitches; i++)
    {
        if(this->logical_topology[switchId][i] != 0)
        {
            if(this->unassignedNode.count(i) != 0)
            {
                this->unassignedNode[i]->embeddedNeighbors++;
            }
        }
    }
}
unsigned int GuranteedEmbedding::getBestNode() {

    double bestValue = 0;
    int bestNode = -1;
    cout << "IN BEST VAlue: Map size: " << this->unassignedNode.size()<< endl;

    for(map<unsigned int, NodeValue*>::iterator iter = this->unassignedNode.begin();
                iter != this->unassignedNode.end(); iter++)
    {
        //cout << "degree ratio: " << iter->second->degreeRatio << endl;
        double selfRatio = this->gamma1*iter->second->degreeRatio+ this->gamma2*iter->second->bandwidthRatio
                + this->gamma3*iter->second->resourceRatio + this->gamma4*(((double)iter->second->embeddedNeighbors)/iter->second->neighborCount);
        //cout << "selfRatio ratio: " << selfRatio << endl;
        if(selfRatio > bestValue && this->currentEmbedding[iter->first] == -1)
        {
            bestValue = selfRatio;
            bestNode = iter->first;
        }
    }
    cout << "best value: "  << bestValue << " best node: "<< bestNode << endl;

    return bestNode;
}

void GuranteedEmbedding::processInputTopology(InputTopology* inputTopology)
{

    double maxNeighbor = 0;
    double maxBandwidth = 0;
    double minBandwidth = DBL_MAX;
    double maxCpu  = 0;
    this->numberOfSwitches = inputTopology->getNumberOfSwitches();

    this->currentEmbedding = new int[this->numberOfSwitches];
    for(unsigned long i = 0; i < this->numberOfSwitches; i++)
        this->currentEmbedding[i] = -1;

    inputTopology->populateTopologyBandwidth(this->logical_topology);
    inputTopology->populateTopologyDelay(this->logical_topology_delay);
    cout << "after delay" <<endl;
    for(unsigned long i = 0; i < this->numberOfSwitches; i++)
    {
        //cout << "lt building" << endl;

        NodeValue *newNode = new NodeValue();

        newNode->neighborCount = getNeighborCount(i);
        if(newNode->neighborCount > maxNeighbor)
            maxNeighbor = newNode->neighborCount;

        newNode->embeddedNeighbors = 0;
        newNode->totalBandwidth = getAggregatedBandwidths(i);

        if(newNode->totalBandwidth > maxBandwidth)
            maxBandwidth = newNode->totalBandwidth;
        if(newNode->totalBandwidth < minBandwidth)
                minBandwidth = newNode->totalBandwidth;

        newNode->totalCPU = 0;
        for(unsigned long j = 0; j < this->numberOfHosts; j++)
        {
            if(this->hosts->getSwitch(j) == i)
            {
                newNode->totalCPU += this->hosts->getCPU(j);
            }
        }
        if(newNode->totalCPU > maxCpu)
            maxCpu = newNode->totalCPU;

        this->unassignedNode[i] = newNode;
        //all PM are feasible initially
        for(unsigned int j = 0; j < this->numberOfPhysicalMachines; j++)
        {
            this->unassignedNode[i]->feasibleHosts.push_back(j);
        }
    }
    //cout << "Before Map" << endl;
    cout << "Map size: " << this->unassignedNode.size()<< endl;

    for(map<unsigned int, NodeValue*>::iterator iter = this->unassignedNode.begin();
            iter != this->unassignedNode.end(); iter++)
    {
        iter->second->bandwidthRatio = iter->second->totalBandwidth/maxBandwidth;
        //iter->second->bandwidthRatio = minBandwidth/iter->second->totalBandwidth;
        iter->second->degreeRatio = iter->second->neighborCount/maxNeighbor;
        iter->second->resourceRatio = iter->second->totalCPU/maxCpu;

    }
}



bool GuranteedEmbedding::isFeasible(long * embedding ) {

    double * bandwidthRequired = new double[this->numberOfPhysicalMachines];
    memset(bandwidthRequired, 0, sizeof(double)*this->numberOfPhysicalMachines);
    double * cpuRequired = new double[this->numberOfPhysicalMachines];
    memset(cpuRequired, 0, sizeof(double)*this->numberOfPhysicalMachines);

    for(unsigned long i = 0; i < this->numberOfSwitches-1; i++)
    {
        cpuRequired[embedding[i]] += this->unassignedNode[i]->totalCPU;
        //cout << cpuRequired[embedding[i]] << endl;
        for(unsigned long j = i+1; j < this->numberOfSwitches; j++)
        {
            if(this->logical_topology[i][j]!= 0)
            {
                if(embedding[i] != embedding[j])
                {
                    bandwidthRequired[embedding[i]]+= this->logical_topology[i][j];
                    bandwidthRequired[embedding[j]]+= this->logical_topology[i][j];

                    cpuRequired[embedding[i]] += this->logical_topology[i][j]*2*this->rho;
                    cpuRequired[embedding[j]] += this->logical_topology[i][j]*2*this->rho;
                }

                if(this->logical_topology_delay[i][j]< this->physicalMachines->getDelay(embedding[i], embedding[j]))
                {
                    //cout << "Delay constraint violated for " << i << " " << j << endl;
                    return false;
                }

            }

        }
    }
    cpuRequired[embedding[this->numberOfSwitches-1]] += this->unassignedNode[this->numberOfSwitches-1]->totalCPU;

    for(unsigned int i = 0; i < this->numberOfPhysicalMachines; i++)
    {
        if(cpuRequired[i] > this->physicalMachines->getCores(i))
        {
            //cout << "CPU constraint violated for " << i << endl;
            return false;
        }
        if(bandwidthRequired[i] > this->physicalMachines->getBandwidth(i))
        {
            //cout << "Bandwidth constraint violated for " << i << " embedded: " << bandwidthRequired[i] << " actual: " << this->physicalMachines->getBandwidth(i)<< endl;
            return false;
        }
    }

    return true;
}

GuranteedEmbedding::~GuranteedEmbedding()
{
    delete [] this->stepProbabilities;
    delete [] this->accumulatedStepProbabilities;
    delete [] this->cpuOfPhysicalMachines;
    delete [] this->currentEmbedding;

    for(unsigned long i = 0; i < this->numberOfSwitches; i++)
    {
        delete[]this->logical_topology[i];
    }

    delete [] this->logical_topology;

    delete [] this->globalBest;
}
void GuranteedEmbedding::runSA()
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
}
unsigned int GuranteedEmbedding::getNumberOfActiveMachines(long * next)
{
    bool* machinesActive = new bool [this->numberOfPhysicalMachines];
    memset(machinesActive, 0, this->numberOfPhysicalMachines*sizeof(bool));
    for(unsigned long i = 0; i < this->numberOfSwitches; i++)
    {
        machinesActive[next[i]] = true;
    }

    unsigned int activeCount = 0;
    for(unsigned int i = 0; i < this->numberOfPhysicalMachines; i++)
    {
        if(machinesActive[i] == true)
            activeCount++;
    }
    return activeCount;
}
bool GuranteedEmbedding::run()
{
    this->globalBest = new long[this->numberOfSwitches];
    cout << "Before greedy " << endl;
    if(generateGreedy() == false)
        return false;

    cout << "AFTER greedy now " << endl;
    cout << "0: " << this->currentEmbedding[0];
    cout << "Max: " << this->currentEmbedding[this->numberOfSwitches];

    for(unsigned int i = 0; i < this->numberOfSwitches; i++)
    {   cout << "GM: " << i << ":" << this->currentEmbedding[i] << endl;
        this->activeMachinesList.push_back( this->currentEmbedding[i]);
        this->globalBest[i] = this->currentEmbedding[i];
    }
    this->numberOfActiveMachines = getNumberOfActiveMachines(this->globalBest);

    this->activeMachinesList.unique();


    isFeasible(this->globalBest);
    cout << "Running SA" << endl;

    long * current = new long [this->numberOfSwitches];
    memcpy(current, this->globalBest, this->numberOfSwitches*sizeof(long));
    this->globalBestCost = cost(this->globalBest);
    cout << "Greedy cost: " << this->globalBestCost  << endl;
    int runCount = 0;
    while(runCount ++ < this->numberOfTrials)
    {
        long * outcomeOfSingleRun;

        simRun(current, outcomeOfSingleRun);

        double singleRunCost = cost(outcomeOfSingleRun);
        cout << "SA single run cost: " << singleRunCost << endl;

        if(singleRunCost < this->globalBestCost)
        {
            cout << "SA Modifies " << endl;
            this->globalBestCost = singleRunCost;
            memcpy(this->globalBest, outcomeOfSingleRun, this->numberOfSwitches*sizeof(long));
        }

        memcpy(current, outcomeOfSingleRun, this->numberOfSwitches*sizeof(long));
        delete [] outcomeOfSingleRun;

    }
    cout << "After SA" << endl;
    isFeasible(this->globalBest);
    for(unsigned int i = 0; i < this->numberOfSwitches; i++)
    {
        cout << "SA: " << i << ":" << this->globalBest[i] << endl;
    }

    generateOutput();

    return true;
}

void GuranteedEmbedding::generateOutput()
{
    cout << "output assignment" << endl;
    for(unsigned long i = 0; i < this->numberOfSwitches; i++)
    {
        this->instertMapping(this->mapping, this->physicalMachines->getIPAddress(this->globalBest[i]));
    }

}
//processing input files
void GuranteedEmbedding::processConfigurationFile(string fileName)
{
    this->alpha = 1;
    this->beta = 1;
    this->gamma1 = 1;
    this->gamma2 = 1;
    this->gamma3 = 1;
    this->gamma4 = 1;
    this->lambda1 = 1;
    this->lambda2 = 1;
    this->rho = 0.0001;
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
        cout << "Unable to open GuranteedEmbedding configuration file: " << fileName <<  endl;

    //Getting the values
    if(eachConfiguration.find("alpha") != eachConfiguration.end())
        alpha = atof(eachConfiguration["alpha"].c_str());

    if(eachConfiguration.find("beta") != eachConfiguration.end())
        beta = atof(eachConfiguration["beta"].c_str());

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

    if(eachConfiguration.find("gamma1") != eachConfiguration.end())
        gamma1 = atof(eachConfiguration["gamma1"].c_str());

    if(eachConfiguration.find("gamma2") != eachConfiguration.end())
        gamma2 = atof(eachConfiguration["gamma2"].c_str());

    if(eachConfiguration.find("gamma3") != eachConfiguration.end())
        gamma3 = atof(eachConfiguration["gamma3"].c_str());

    if(eachConfiguration.find("gamma4") != eachConfiguration.end())
        gamma4 = atof(eachConfiguration["gamma4"].c_str());

    if(eachConfiguration.find("lambda1") != eachConfiguration.end())
        lambda1 = atof(eachConfiguration["lambda1"].c_str());

    if(eachConfiguration.find("lambda2") != eachConfiguration.end())
        lambda2 = atof(eachConfiguration["lambda2"].c_str());

    if(eachConfiguration.find("rho") != eachConfiguration.end())
        rho = atof(eachConfiguration["rho"].c_str());

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


void GuranteedEmbedding::generateInitalState(long *& next)
{
    next = new long[this->numberOfSwitches];
    for (unsigned long i = 0; i < this->numberOfSwitches; i++)
    {
        long physicalMachine = unifRand(this->numberOfPhysicalMachines)-1;
        next[i] = physicalMachine;
    }
}



void GuranteedEmbedding::printCost(long * next)
{

}
double GuranteedEmbedding::cost(long * next)
{

    long edgeCount = 0;
    double bandwidth = 0;

    //cross partition link and bandwidth measurement
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
    unsigned int activeCount= this->getNumberOfActiveMachines(next);

    return this->alpha*edgeCount + this->beta*activeCount;
}


void GuranteedEmbedding::successor(long* current, long * &next)
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
        long destiantionPhysicalMachineIndex = unifRand(this->numberOfActiveMachines)-1;

        for (list<unsigned int>::iterator it=this->activeMachinesList.begin();
                it!=this->activeMachinesList.end(); ++it)
        {
            if(destiantionPhysicalMachineIndex == 0)
            {
                next[switchToChange] = *it;
                break;
            }

            destiantionPhysicalMachineIndex--;
        }

    }
}


void GuranteedEmbedding::simRun(long * start, long *&final)
{
    //cout << "SA Started" << endl;

    long * current = new long[this->numberOfSwitches];
    memcpy(current, start, this->numberOfSwitches*sizeof(long));

    long * pathBest =   new long[this->numberOfSwitches];
    memcpy(pathBest, start, this->numberOfSwitches*sizeof(long));

    int stepCount = 0;
    double currentTemperature = this->initalTemperature;

    double currentCost = cost(start);
    double pathBestCost = cost(pathBest);

    while(stepCount++ < this->numberOfSteps)
    {
        long * next;
        successor(current, next);
        if(isFeasible(next) == false)
            continue;
        //cout << "At least feasible " << endl;
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
                cout << "worse taken" << endl;

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
double GuranteedEmbedding::unifRand()
{
    return rand() / double(RAND_MAX);
    //return distribution(generator);
}
//
// Generate a random number in a real interval.
// param a one end point of the interval
// param b the other end of the interval
// return a inform rand numberin [a,b].
double GuranteedEmbedding::unifRand(double a, double b)
{
    return (b-a)*unifRand() + a;
}
//
// Generate a random integer between 1 and a given value.
// param n the largest value
// return a uniform random value in [1,...,n]
long GuranteedEmbedding::unifRand(long n)
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
void GuranteedEmbedding::seed()
{
    srand(time(0));
}
