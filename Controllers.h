/*
 * Controllers.h
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
 */

#ifndef CONTROLLERS_H_
#define CONTROLLERS_H_
#include <string>
#include <vector>
using namespace std;

class Controllers {
	struct ControllerAttribute
	{
		unsigned int controller_id;
		string ip;
		string port;
	};

	static Controllers* controllers;

	Controllers();

	unsigned int numberOfControllers;
	vector<ControllerAttribute > controllerIdVector;
public:

	static Controllers* getControllers();
	void populateControllers(string fileName);

	unsigned int getNumberOfControllers();

	string getIPAddress(unsigned int ctrlId);
	string getPort(unsigned int ctrlId);

	virtual ~Controllers();
};

#endif /* CONTROLLERS_H_ */
