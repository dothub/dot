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
 * Util.cpp
 *
 *  Created on: 2013-08-12
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "Util.h"
#include <sstream>
#include <iomanip>

void Util::parseKeyValue(string input, string& key, string& value,
        char delimeter) {


    stringstream tokenizer(input);

    if(getline(tokenizer, key, delimeter) == false)
        key = "";

    if(getline(tokenizer, value, delimeter) == false)
        value = "";

}

string Util::getFileName(const string& strPath)
{
        size_t iLastSeparator = 0;
        return strPath.substr((iLastSeparator = strPath.find_last_of("/")) != string::npos ? iLastSeparator + 1 : 0, strPath.size());
}

string Util::getPathName(const string& strPath)
{
        size_t iLastSeparator = 0;
        return strPath.substr(0, (iLastSeparator = strPath.find_last_of("/")) == string::npos ? 0: iLastSeparator+1);
}

void Util::parseString(string input, vector<string>* &tokens, char delimeter) {

    tokens = new vector<string>();

    stringstream tokenizer(input);

    string eachPart;
    while(getline(tokenizer, eachPart, delimeter))
    {
        tokens->push_back(eachPart);
    }

}

string Util::intToHexString(unsigned long input, unsigned int width)
{
    ostringstream stream;

    if(width != 0)
        stream << setw(width);

    stream << setfill('0');
    stream << hex << input;

    return stream.str();
}

