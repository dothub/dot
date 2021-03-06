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
 * Credentials.h
 *
 *  Created on: 2013-08-12
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef CREDENTIALS_H_
#define CREDENTIALS_H_
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
class Credentials {

    LoggerPtr* selfLogger;
    static Credentials* credentials;

    string userName;
    string password;
    string key;

    Credentials();
public:
    static Credentials* getCredentials();
   
     /**
    * The function to populate credentials from a file.
    * @param fileName - Name of the file
    */
 
    void populateCredentials(string fileName);

     /**
    * The function returns the username.
    * @return Name of the user as a string
    */

    string getUserName();

    virtual ~Credentials();
};

#endif /* CREDENTIALS_H_ */
