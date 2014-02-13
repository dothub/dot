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
 * GuranteedEmbedding.h
 *
 *  Created on: 2013-08-31
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef GURANTEEDEMBEDDING_H_
#define GURANTEEDEMBEDDING_H_

#include "PartitioningAlgorithm.h"
#include "PhysicalMachines.h"
#include "InputTopology.h"
#include "Mapping.h"
#include "Hosts.h"
#include <vector>
#include <list>
#include <string>
#include <map>


using namespace std;

class Mapping;

class PhysicalMachineValue{
public:
            double totalCPU;
            double totalBandwidth;

            double cpuForSwitches;
            double cpuForGateways;
            double bandwdithAllocated;
            bool active;

            list<unsigned long> embeddedSwitches;

};




class NodeValue{
public:

            double degreeRatio;
            double bandwidthRatio;
            double resourceRatio;
            unsigned int embeddedNeighbors;
            unsigned int neighborCount;
            double totalCPU;
            double totalBandwidth;

            list<unsigned int> feasibleHosts;

};


class GuranteedEmbedding: public PartitioningAlgorithm {
        //inputs

        double alpha;
        double beta;

        //sa parameters
        double initalTemperature;
        double reductionRate;
        double minimumTemp;
        int numberOfSteps;
        int numberOfTrials;
        int typesOfSteps;
        double * stepProbabilities;
        long * accumulatedStepProbabilities;

        double gamma1, gamma2, gamma3, gamma4;
        double lambda1, lambda2;

        double **logical_topology;//stores the logical topology in adjacency matrix
        double **logical_topology_delay;//stores the logical topology  delay in adjacency matrix
        unsigned long getNeighborCount(unsigned int switchId);
        double getAggregatedBandwidths(unsigned int switchId);
        void updateNeighborsEmbeddedCount(unsigned long switchId);




        unsigned long numberOfSwitches;
        unsigned int numberOfPhysicalMachines;
        unsigned long numberOfHosts;
        unsigned int* cpuOfPhysicalMachines;

        //Greedy
        bool generateGreedy();
        double rho;
        int * currentEmbedding;
        map<unsigned int, NodeValue*> unassignedNode;
        vector<PhysicalMachineValue*> machines;
        unsigned int getBestPhysicalMachine(unsigned long switchId);
        unsigned int getBestNode();//return the best node to embed
        void assignSwitch(unsigned long switch_id, unsigned int physicalMachine);
        void getFeasibleValue(unsigned long switch_id, unsigned int physicalMachine,
                double &repaidBandwidth, double& neighborEmbedded);
        unsigned int numberOfActiveMachines;
        list<unsigned int> activeMachinesList;
        unsigned int getNumberOfActiveMachines(long * mapping);




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
        void processInputTopology(InputTopology* inputTopology);
        void processPhysicalMachines();

        Mapping* mapping;
        PhysicalMachines* physicalMachines;
        Hosts* hosts;


        void runSA();

        bool isFeasible(long * embedding );

    public:
        bool  run();
        GuranteedEmbedding(string SAConfigurationFile, InputTopology * inputTopology, PhysicalMachines* physicalMachines, Mapping * mapping, Hosts* hosts);
        ~GuranteedEmbedding();
};

#endif /* GURANTEEDEMBEDDING_H_ */
