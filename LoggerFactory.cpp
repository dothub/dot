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
 * LoggerFactory.cpp
 *
 *  Created on: 2014-02-27
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "LoggerFactory.h"
#include <iostream>

LoggerPtr LoggerFactory::loggerMain(Logger::getLogger("main"));
LoggerPtr LoggerFactory::loggerAbstractLink(Logger::getLogger("AbstractLink"));
LoggerPtr LoggerFactory::loggerAbstractSwitch(Logger::getLogger("AbstractSwitch"));
LoggerPtr LoggerFactory::loggerAbstractVM(Logger::getLogger("AbstractVM"));
LoggerPtr LoggerFactory::loggerCommandExecutor(Logger::getLogger("CommandExecutor"));
LoggerPtr LoggerFactory::loggerConfigurations(Logger::getLogger("Configurations"));
LoggerPtr LoggerFactory::loggerControllers(Logger::getLogger("Controllers"));
LoggerPtr LoggerFactory::loggerCredentials(Logger::getLogger("Credentials"));
LoggerPtr LoggerFactory::loggerCutEdge(Logger::getLogger("CutEdge"));
LoggerPtr LoggerFactory::loggerDeployDOT(Logger::getLogger("DeployDOT"));
LoggerPtr LoggerFactory::loggerDOT(Logger::getLogger("DOT"));
LoggerPtr LoggerFactory::loggerDOTTopology(Logger::getLogger("DOTTopology"));
LoggerPtr LoggerFactory::loggerEmbeddingAlgorithm(Logger::getLogger("EmbeddingAlgorithm"));
LoggerPtr LoggerFactory::loggerGlobal(Logger::getLogger("Global"));
LoggerPtr LoggerFactory::loggerGREInterface(Logger::getLogger("GREInterface"));
LoggerPtr LoggerFactory::loggerGuaranteedEmbedding(Logger::getLogger("GuaranteedEmbedding"));
LoggerPtr LoggerFactory::loggerInterface(Logger::getLogger("Interface"));
LoggerPtr LoggerFactory::loggerKVMWithLibvirt(Logger::getLogger("KVMWithLibvirt"));
LoggerPtr LoggerFactory::loggerLink(Logger::getLogger("Link"));
LoggerPtr LoggerFactory::loggerLoggerFactory(Logger::getLogger("LoggerFactory"));
LoggerPtr LoggerFactory::loggerLogicalTopology(Logger::getLogger("LogicalTopology"));
LoggerPtr LoggerFactory::loggerMapping(Logger::getLogger("Mapping"));
LoggerPtr LoggerFactory::loggerOVS_1_10(Logger::getLogger("OVS_1_10"));
LoggerPtr LoggerFactory::loggerPhysicalMachines(Logger::getLogger("PhysicalMachines"));
LoggerPtr LoggerFactory::loggerSwitch2Controller(Logger::getLogger("Switch2Controller"));
LoggerPtr LoggerFactory::loggerSwitch(Logger::getLogger("Switch"));
LoggerPtr LoggerFactory::loggerTunnel(Logger::getLogger("Tunnel"));
LoggerPtr LoggerFactory::loggerUtil(Logger::getLogger("Util"));
LoggerPtr LoggerFactory::loggerVLink(Logger::getLogger("VLink"));
LoggerPtr LoggerFactory::loggerVMs(Logger::getLogger("VMs"));


LoggerFactory* LoggerFactory::loggerFactory = NULL;

LoggerFactory::LoggerFactory() {

}

void LoggerFactory::initateFactory()
{

    //assigning the loggers to map
    this->loggerMap["main"] = &loggerMain;
    this->loggerMap["AbstractLink"] = &loggerAbstractLink;
    this->loggerMap["AbstractSwitch"] = &loggerAbstractSwitch;
    this->loggerMap["AbstractVM"] = &loggerAbstractVM;
    this->loggerMap["CommandExecutor"] = &loggerCommandExecutor;
    this->loggerMap["Configurations"] = &loggerConfigurations;
    this->loggerMap["Controllers"] = &loggerControllers;
    this->loggerMap["Credentials"] = &loggerCredentials;
    this->loggerMap["CutEdge"] = &loggerCutEdge;
    this->loggerMap["DeployDOT"] = &loggerDeployDOT;
    this->loggerMap["DOT"] = &loggerDOT;
    this->loggerMap["DOTTopology"] = &loggerDOTTopology;
    this->loggerMap["EmbeddingAlgorithm"] = &loggerEmbeddingAlgorithm;
    this->loggerMap["Global"] = &loggerGlobal;
    this->loggerMap["GREInterface"] = &loggerGREInterface;
    this->loggerMap["GuaranteedEmbedding"] = &loggerGuaranteedEmbedding;
    this->loggerMap["Interface"] = &loggerInterface;
    this->loggerMap["KVMWithLibvirt"] = &loggerKVMWithLibvirt;
    this->loggerMap["Link"] = &loggerLink;
    this->loggerMap["LoggerFactory"] = &loggerLoggerFactory;
    this->loggerMap["LogicalTopology"] = &loggerLogicalTopology;
    this->loggerMap["Mapping"] = &loggerMapping;
    this->loggerMap["OVS_1_10"] = &loggerOVS_1_10;
    this->loggerMap["PhysicalMachines"] = &loggerPhysicalMachines;
    this->loggerMap["Switch2Controller"] = &loggerSwitch2Controller;
    this->loggerMap["Switch"] = &loggerSwitch;
    this->loggerMap["Tunnel"] = &loggerTunnel;
    this->loggerMap["Util"] = &loggerUtil;
    this->loggerMap["VLink"] = &loggerVLink;
    this->loggerMap["VMs"] = &loggerVMs;
   
      
    //Self Logger     
    loggerPtr = &loggerLoggerFactory;

    //Debug Mode is kept on for LoggerFactory
    (*loggerPtr)->setLevel(Level::getDebug());
        
    DOMConfigurator::configure(Global::logConfigFile);

}

LoggerFactory* LoggerFactory::getLoggerFactory()
{
    if(loggerFactory == NULL)
    {
        loggerFactory = new LoggerFactory();
        loggerFactory->initateFactory();
    }
    
    return loggerFactory; 
}

LoggerPtr* LoggerFactory::getLogger(string className)
{
    if(this->loggerMap.find(className) == this->loggerMap.end())
    {
      
        LOG4CXX_ERROR((*loggerPtr), 
            "There is no logger for class " << className);
        return NULL;
    }
    
    if(Global::debugMode)
        (*loggerMap[className])->setLevel(Level::getDebug());

    return loggerMap[className];

}

LoggerFactory::~LoggerFactory() {
    // TODO Auto-generated destructor stub
}


