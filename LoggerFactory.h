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
 * LoggerFactory.h
 *
 *  Created on: 2014444-02-27
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef LOGGERFACTORY_H_
#define LOGGERFACTORY_H_
#include "Global.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include <string>
#include <map>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;

class LoggerFactory {

    LoggerPtr* loggerPtr;

    LoggerFactory();
    void initateFactory();

    //List of static loggers
    static LoggerPtr loggerMain;
    static LoggerPtr loggerAbstractLink;
    static LoggerPtr loggerAbstractSwitch;
    static LoggerPtr loggerAbstractVM;
    static LoggerPtr loggerCommandExecutor;
    static LoggerPtr loggerConfigurations;
    static LoggerPtr loggerControllers;
    static LoggerPtr loggerCredentials;
    static LoggerPtr loggerCutEdge;
    static LoggerPtr loggerDeployDOT;
    static LoggerPtr loggerDOT;
    static LoggerPtr loggerDOTTopology;
    static LoggerPtr loggerEmbeddingAlgorithm;
    static LoggerPtr loggerGlobal;
    static LoggerPtr loggerGREInterface;
    static LoggerPtr loggerGuaranteedEmbedding;
    static LoggerPtr loggerInterface;
    static LoggerPtr loggerKVMWithLibvirt;
    static LoggerPtr loggerLink;
    static LoggerPtr loggerLoggerFactory;
    static LoggerPtr loggerLogicalTopology;
    static LoggerPtr loggerMapping;
    static LoggerPtr loggerOVS_1_10;
    static LoggerPtr loggerPhysicalMachines;
    static LoggerPtr loggerSwitch2Controller;
    static LoggerPtr loggerSwitch;
    static LoggerPtr loggerTunnel;
    static LoggerPtr loggerUtil;
    static LoggerPtr loggerVLink;
    static LoggerPtr loggerVMs;
 
    
    //end list of static loggers

    static LoggerFactory* loggerFactory;

    map<string, LoggerPtr*> loggerMap;
public:
    static LoggerFactory* getLoggerFactory();

    LoggerPtr* getLogger(string className);

    virtual ~LoggerFactory();
};

#endif /* LOGGERFACTORY_H_ */
