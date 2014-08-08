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
 * Util.h
 *
 *  Created on: 2013-08-12
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#ifndef UTIL_H_
#define UTIL_H_
#include <string>
#include <vector>
#include <log4cxx/logger.h>
using namespace log4cxx;

using namespace std;
namespace util
{
class Util {
    static LoggerPtr logger;

public:
    static bool onlySpaces(string& input); 
    static void bipartiateString(string &input, vector<string>& tokens, char delimeter);
    static void  parseKeyValue(string& input, string& key, string& value, char delimeter);
    static void parseString(string& input, vector<string>& tokens, char delimeter);
    static string intToHexString(unsigned long input, unsigned int width=0);
    static string getFileName(const string& strPath);
    static string getPathName(const string& strPath);
    static string intToMac(unsigned long input);
    static string intToIP(int input);
    static int ipToInt(string ip);

};
}
#endif /* UTIL_H_ */
