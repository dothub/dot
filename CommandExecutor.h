/*
 * CommandExecutor.h
 *
 *  Created on: 2013-08-05
 *      Author: ar3roy
 */

#ifndef COMMANDEXECUTOR_H_
#define COMMANDEXECUTOR_H_

#include <string>
#include "Credentials.h"
using namespace std;

class CommandExecutor
{
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
