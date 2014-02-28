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
 * LogicalTopology.cpp
 *
 *  Created on: 2013-08-06
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "LogicalTopology.h"

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stddef.h>

using namespace std;

LogicalTopology* LogicalTopology::logicalTopology=NULL;


LogicalTopology* LogicalTopology:: getLogicalTopology()
{
    if(logicalTopology == NULL)
        logicalTopology = new LogicalTopology();

    return logicalTopology;
}

unsigned long LogicalTopology::getNumberOfSwitches()
{
    return this->numberOfSwitches;
}

void LogicalTopology::populateTopology(string fileName) {


    ifstream fin(fileName.c_str());

    if(fin.is_open())
    {
        unsigned long numberOfEdges;
        fin >> this->numberOfSwitches;
        fin >> numberOfEdges;

        this->topology = new LinkProperty *[this->numberOfSwitches];

        for(unsigned long i = 0; i < this->numberOfSwitches; i++)
        {
            this->topology[i] = new LinkProperty [this->numberOfSwitches];
        }

        for(unsigned long i = 0; i < numberOfEdges; i++)
        {
            string source, destination;
            double bandwidth, delay;
            fin >> source >> destination >> bandwidth >> delay;

            this->topology[atol(source.substr(1).c_str())-1][atol(destination.substr(1).c_str())-1].bandwidth = bandwidth;
            this->topology[atol(destination.substr(1).c_str())-1][atol(source.substr(1).c_str())-1].bandwidth = bandwidth;
            this->topology[atol(source.substr(1).c_str())-1][atol(destination.substr(1).c_str())-1].delay = delay;
            this->topology[atol(destination.substr(1).c_str())-1][atol(source.substr(1).c_str())-1].delay = delay;

        }

        fin.close();

    }
    else
        cout << "Unable to open topology file: " << fileName << endl;

}

void LogicalTopology::populateTopologyBandwidth(double**& topologyBandwidth) {

    topologyBandwidth = new double* [this->numberOfSwitches];

    for(unsigned long i = 0; i < this->numberOfSwitches; i++)
    {
        topologyBandwidth[i] = new double[this->numberOfSwitches];

        for(unsigned long j = 0; j < this->numberOfSwitches; j++)
            topologyBandwidth[i][j] = this->topology[i][j].bandwidth;
    }
}

void LogicalTopology::populateTopologyDelay(double**& topologyDelay) {

    topologyDelay = new double* [this->numberOfSwitches];

    for(unsigned long i = 0; i < this->numberOfSwitches; i++)
    {
        topologyDelay[i] = new double[this->numberOfSwitches];

        for(unsigned long j = 0; j < this->numberOfSwitches; j++)
            topologyDelay[i][j] = this->topology[i][j].delay;
    }
}

LogicalTopology::LogicalTopology() {


}

double LogicalTopology::getLinkDelay(unsigned long switch1,
        unsigned long switch2) {

    return this->topology[switch1][switch2].delay;
}

double LogicalTopology::getLinkBandwidth(unsigned long switch1,
        unsigned long switch2) {

    return this->topology[switch1][switch2].bandwidth;
}

bool LogicalTopology::isNeighbor(unsigned long switch1, unsigned long switch2) {
    return this->topology[switch1][switch2].bandwidth != 0 || this->topology[switch2][switch1].bandwidth != 0;
}

LogicalTopology::~LogicalTopology() {

}

