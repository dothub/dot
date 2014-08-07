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
* Copyright 2011-2014 dothub.org
*/

/*
 * command_executor.cpp
 *
 *  Created on: 2013-08-05
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "command_executor.h"

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>

using namespace std;
using namespace executor;

LoggerPtr CommandExecutor::logger = Logger::getLogger("CommandExecutor");

string CommandExecutor::execute(string command)
{
    LOG4CXX_DEBUG(logger, "Command: " << command);

    FILE * pipe = popen(command.c_str(), "r");

    if(!pipe)
        return "ERROR";

    char buffer[128];
    string result;

    while(!feof(pipe))
    {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    pclose(pipe);

    //removing the newline
    if(result.size() > 0)  
        result.resize(result.size() - 1); 
    
    LOG4CXX_DEBUG(logger, "Result: "<< result);

    return result; 
}


string CommandExecutor::executeLocal(string command) {

    return execute(command);
}

string CommandExecutor::executeScriptLocal(string filePath, string fileName, string parameters) {

    ostringstream toExecute;
    toExecute << filePath << fileName << " " << parameters;

    return execute(toExecute.str());
}

string CommandExecutor::executeRemote(string machine, string command, 
    string user, string key){

    ostringstream toExecute;

    toExecute << "ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no ";

    if(key.compare("") != 0)
        toExecute << "-i " << key << " ";

    toExecute << user <<"@" << machine
            << " \"" << command << "\"";
    

    return execute(toExecute.str());
}

string CommandExecutor::executeScriptRemote(string machine, string filePath, 
    string fileName, string parameters, string user, string key) {

    ostringstream fileWithPath;
    fileWithPath << filePath << fileName;

    copyUsingLocal("localhost", machine, fileWithPath.str(), "~/", user, key);

    ostringstream remoteCommand;
    remoteCommand << "./" << fileName << " " << parameters;

    string output = executeRemote(machine, remoteCommand.str(), user, key);

    //deleting the script from the remote machine
    ostringstream removeCommand;
    removeCommand << "rm -r ~/" << fileWithPath.str();

    executeRemote(machine, removeCommand.str(), user, key);

    return output;
}

void CommandExecutor::copyUsingLocal(string sourceMachine,
        string destinationMachine, string sourcePath, string destinationPath,
        string user, string key, bool isFolder) {

    ostringstream toExecute;

    toExecute << "scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no ";
    if(isFolder)
        toExecute << "-r ";
    if(sourceMachine.compare("localhost")==0)
        toExecute << sourcePath << " ";
    else
    {
        if(key.compare("") != 0)
            toExecute << "-i " << key << " ";

        toExecute << user << "@" << sourceMachine << ":" << sourcePath << " ";
    }
    
    if(destinationMachine.compare("localhost")==0)
            toExecute << destinationPath;
    else
    {
        if(key.compare("") != 0)
            toExecute << "-i " << key << " ";

        toExecute << user <<"@" << destinationMachine << ":" << destinationPath;

    }
    
    execute(toExecute.str());

}

CommandExecutor::CommandExecutor() {
}

