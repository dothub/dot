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
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef CONTROLLERS_H_
#define CONTROLLERS_H_
#include <string>
#include <vector>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;


/**
* This singleton class stores all controller inforamtion.
*/

class Controllers {
    LoggerPtr* selfLogger;
    
    
    /**
    * This structure stores ID,IP Address and Port of a controller.
    */
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
    
    
    /**
    * The function to populate controller from a file.
    * @param fileName - Name of the file
    */
    void populateControllers(string fileName);

    /**
    * @retuur- Returns the number of controllers
    */
    unsigned int getNumberOfControllers();
    
    /**
    * The function to return the ip address of a controller
    * @param- ctrlId - Controller ID.
    * @return - IP address of the controller
    */
    string getIPAddress(unsigned int ctrlId);
    

    /**
    * The function to return the portof a controller
    * @param- ctrlId - Controller ID.
    * @return - Port of the controller
    */
    string getPort(unsigned int ctrlId);

    /**
    * Destructor of the class.
    */

    virtual ~Controllers();
};

#endif /* CONTROLLERS_H_ */
