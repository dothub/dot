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
