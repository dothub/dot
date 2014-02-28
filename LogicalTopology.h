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
 * LogicalTopology.h
 *
 *  Created on: 2013-08-06
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef LOGICALTOPOLOGY_H_
#define LOGICALTOPOLOGY_H_

#include <string>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;

class LogicalTopology {
    LoggerPtr* selfLogger;

    struct LinkProperty
    {
        double bandwidth;
        double delay;

        LinkProperty():bandwidth(0),delay(0){}
    };

    LinkProperty ** topology;

    static LogicalTopology* logicalTopology;
    unsigned long numberOfSwitches;

    LogicalTopology();

public:
    static LogicalTopology* getLogicalTopology();

    void populateTopology(string fileName);


    unsigned long getNumberOfSwitches();
    void populateTopologyBandwidth(double ** & topologyBandwidth);
    void populateTopologyDelay(double ** & topologyDelay);

    double getLinkDelay(unsigned long switch1, unsigned long switch2);
    double getLinkBandwidth(unsigned long switch1, unsigned long switch2);

    bool isNeighbor(unsigned long switch1, unsigned long switch2);

    virtual ~LogicalTopology();
};

#endif /* LOGICALTOPOLOGY_H_ */
