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
 * GuaranteedEmbedding.h
 *
 *  Created on: 2013-08-31
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef GUARANTEEDEMBEDDING_H_
#define GUARANTEEDEMBEDDING_H_

#include "EmbeddingAlgorithm.h"
#include "PhysicalMachines.h"
#include "LogicalTopology.h"
#include "Mapping.h"
#include "VMs.h"
#include <vector>
#include <list>
#include <string>
#include <map>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

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

            list<unsigned int> feasibleVMs;

};


class GuaranteedEmbedding: public EmbeddingAlgorithm {
        //inputs

        double alpha;
        double beta;

        LoggerPtr* selfLogger;

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
        unsigned long numberOfVMs;
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
        void processLogicalTopology(LogicalTopology* logicalTopology);
        void processPhysicalMachines();

        Mapping* mapping;
        PhysicalMachines* physicalMachines;
        VMs* vms;


        void runSA();

        bool isFeasible(long * embedding );

    public:
        bool  run();
        GuaranteedEmbedding(string SAConfigurationFile, LogicalTopology * logicalTopology, PhysicalMachines* physicalMachines, Mapping * mapping, VMs* vms);
        ~GuaranteedEmbedding();
};

#endif /* GUARANTEEDEMBEDDING_H_ */
