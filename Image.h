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
 * Image.h
 *
 *  Created on: 2013-08-28
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef IMAGE_H_
#define IMAGE_H_
#include <string>
#include "CommandExecutor.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "Global.h"

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;


/**
* This is the base class for provisioning different classes of virtual switch.
*/
class Image {

    /**
    * The event logger of this class.
    */
    LoggerPtr* selfLogger;
 

    unsigned short id;
    string type;
    string baseImage;

public:
    /**
    * Constructor of the class.
    * @param commandExec - Pointer to the global object of CommandExecutor.
    */
    Image(unsigned short image_id, string& type, 
        string& baseImage);


    short getId();

    string getType();

    string getBaseImage();

    /**
    * Destructor of the class.
    */
    virtual ~Image();
};

#endif /* IMAGE_H_ */
