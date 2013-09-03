/*
 * Controllers.cpp
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
 */

#include "Controllers.h"
#include "cstdlib"
#include <iostream>
#include <fstream>

Controllers* Controllers::controllers = NULL;

Controllers::Controllers() {
}

Controllers* Controllers::getControllers() {

	if(controllers == NULL)
		controllers = new Controllers();

		return controllers;
	}

void Controllers::populateControllers(string fileName) {
	ifstream fin(fileName.c_str());

	if(fin.is_open())
	{
		fin >> this->numberOfControllers;


		for(unsigned int i = 0; i < this->numberOfControllers; i++)
		{
			string ctrl_str, ip, port;
			fin >> ctrl_str >> ip >> port;

			ControllerAttribute newCtrl;
			newCtrl.controller_id = atoi(ctrl_str.substr(1).c_str())-1;
			newCtrl.ip = ip;
			newCtrl.port = port;

			this->controllerIdVector.push_back(newCtrl);

		}


		fin.close();
	}
	else
		cout << "Unable to open controller file: " << fileName << endl;
}

unsigned int Controllers::getNumberOfControllers() {

	return this->numberOfControllers;
}

string Controllers::getIPAddress(unsigned int ctrlId) {

	if(ctrlId < 0 || ctrlId >= this->controllerIdVector.size())
	{
		cout << "Invalid Controller ID " << ctrlId << endl;
		return "None";
	}

	return this->controllerIdVector[ctrlId].ip;
}

string Controllers::getPort(unsigned int ctrlId) {
	if(ctrlId < 0 || ctrlId >= this->controllerIdVector.size())
	{
		cout << "Invalid Controller ID " << ctrlId << endl;
		return "None";
	}

	return this->controllerIdVector[ctrlId].port;
}

Controllers::~Controllers() {
}

