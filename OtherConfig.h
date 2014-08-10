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
 * OtherConfig.h
 *
 *  Created on: 2013-08-12
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef OTER_CONFIG_H_
#define OTER_CONFIG_H_
#include <string>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;

/**
* This singleton class stores inforamtion about user credentials.
*/
class OtherConfig {

    LoggerPtr* selfLogger;

    string of_version;

public:
     OtherConfig();
   
     /**
    * The function to populate credentials from a file.
    * @param fileName - Name of the file
    */
 
    void populate(string fileName);

     /**
    * The function returns the Of version.
    * @return version of openflow as a string
    */

    string getOFVersion();

    virtual ~OtherConfig();
};

#endif /* OTER_CONFIG_H_ */
