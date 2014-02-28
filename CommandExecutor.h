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
 * CommandExecutor.h
 *
 *  Created on: 2013-08-05
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef COMMANDEXECUTOR_H_
#define COMMANDEXECUTOR_H_

#include <string>
#include "Credentials.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;

class CommandExecutor
{

    LoggerPtr* selfLogger;

    Credentials* credential;

    string localIP;
    string localName;

    string execute(string command);

    void copyUsingLocal(string sourceMachine, string destinationMachine,
            string sourcePath, string destinationPath, bool isFolder=false);
public:

    string executeLocal(string command);
    string  executeScriptLocal(string filePath, string fileName, string parameters="");

    string executeRemote(string machine, string command);
    string executeScriptRemote(string machine, string filePath, string fileName, string parameters="");

    void copyContent(string sourceMachine, string destinationMachine,
                string sourcePath, string destinationPath, bool isFolder=false);

    CommandExecutor(Credentials* credential, string localIP, string localName);

};

#endif /* COMMANDEXECUTOR_H_ */
