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
 * command_executor.h
 *
 *  Created on: 2013-08-05
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include <string>
#include <log4cxx/logger.h>

using namespace log4cxx;
using namespace std;

namespace executor
{

class CommandExecutor
{
    static LoggerPtr logger; 
public: 
    CommandExecutor();
    static void executeBackground(string command);
    static string execute(string command);
    static string executeLocal(string command);
    static string executeScriptLocal(string filePath, string fileName, string parameters="");
    static void executeScriptBackground(string filePath, string fileName, string parameters="");
    static string executeRemote(string machine, string command, string user, string key="");
    static string executeScriptRemote(string machine, string filePath, string fileName, string parameters, string user, string key="");
    static void copyUsingLocal(string sourceMachine, string destinationMachine, string sourcePath, string destinationPath,
        string user, string key="", bool isFolder=false);

};
}
#endif /*COMMAND_EXECUTOR_H*/
