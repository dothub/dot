/*
 * CommandExecutor.cpp
 *
 *  Created on: 2013-08-05
 *      Author: ar3roy
 */

#include "CommandExecutor.h"

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>

using namespace std;


string CommandExecutor::execute(string command)
{
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

	return result;
	//return "";
}


string CommandExecutor::executeLocal(string command) {

	return this->execute(command);
}

string CommandExecutor::executeScriptLocal(string filePath, string fileName, string parameters) {

	ostringstream toExecute;
	toExecute << filePath << fileName << " " << parameters;

	return this->execute(toExecute.str());
}

string CommandExecutor::executeRemote(string machine, string command)
{
	ostringstream toExecute;

	toExecute << "ssh " << this->credential->getUserName() <<"@" << machine
			<< " \"" << command << "\"";
	//cout << toExecute.str() << endl;

	return this->execute(toExecute.str());
}

string CommandExecutor::executeScriptRemote(string machine, string filePath, string fileName, string parameters) {

	ostringstream fileWithPath;
	fileWithPath << filePath << fileName;

	this->copyUsingLocal("localhost", machine, fileWithPath.str(), "~/");

	ostringstream remoteCommand;
	remoteCommand << "./" << fileName << " " << parameters;
	return this->executeRemote(machine, remoteCommand.str());

}

void CommandExecutor::copyUsingLocal(string sourceMachine,
		string destinationMachine, string sourcePath, string destinationPath,
		bool isFolder) {

	ostringstream toExecute;

	toExecute << "scp ";
	if(isFolder)
		toExecute << "-r ";
	if(sourceMachine.compare("localhost")==0)
		toExecute << sourcePath << " ";
	else
		toExecute << this->credential->getUserName() << "@" << sourceMachine << ":" << sourcePath << " ";

	if(destinationMachine.compare("localhost")==0)
			toExecute << destinationPath;
	else
		toExecute << this->credential->getUserName() <<"@" << destinationMachine << ":" << destinationPath;

	cout << toExecute.str() << endl;
	this->execute(toExecute.str());

}

void CommandExecutor::copyContent(string sourceMachine,
		string destinationMachine, string sourcePath, string destinationPath,
		bool isFolder) {

	//TODO: to be written
	copyUsingLocal(sourceMachine, destinationMachine, sourcePath, destinationPath, isFolder);
}

CommandExecutor::CommandExecutor(Credentials* credential, string localIP, string localName) {

	this->credential = credential;
	this->localIP = localIP;
	this->localName = localName;
}



