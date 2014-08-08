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

#include "util.h"
#include <sstream>
#include <iomanip>
#include <math.h>  
#include <cstdlib>

using namespace util;

LoggerPtr Util::logger = Logger::getLogger("Util");

void Util::bipartiateString(string &input, vector<string>& tokens, char delimeter)
{
    string left = input.substr(0, input.find_first_of(delimeter));
    string right = input.substr(input.find_first_of(delimeter)+1);

    tokens.push_back(left);
    tokens.push_back(right);
}
    

bool Util::onlySpaces(string& input) {

   return input.find_first_not_of(" \t\n\v\f\r") == input.npos;
}

void Util::parseKeyValue(string& input, string& key, string& value,
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
        return strPath.substr((iLastSeparator = strPath.find_last_of("/")) 
                    != string::npos ? iLastSeparator + 1 : 0, strPath.size());
}

string Util::getPathName(const string& strPath)
{
        size_t iLastSeparator = 0;
        return strPath.substr(0, (iLastSeparator = strPath.find_last_of("/")) 
               == string::npos ? 0: iLastSeparator+1);
}

void Util::parseString(string& input, vector<string>& tokens, char delimeter) {

    //tokens = new vector<string>();

    stringstream tokenizer(input);

    string eachPart;
    while(getline(tokenizer, eachPart, delimeter))
    {
        tokens.push_back(eachPart);
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

string Util::intToMac(unsigned long input)
{
    ostringstream stream;

    stream << setw(12);

    stream << setfill('0');
    stream << hex << input;
  
        
    string mac (17, ':');
    
    string hexedInput = stream.str();
    
    int i = 0;
    int j = 0;
    while(i < 17)
    {
        mac[i++] = hexedInput[j++];
        
        if((i % 3) == 2)
            i++;
    }
    

    return mac;
}

string Util::intToIP(int input)
{
    
    unsigned char bytes[4];
    ostringstream stream;

    
    for(int i=0; i < 4; i++) 
         bytes[i] = (input >> i*8) & 0xFF;
    
    for(int i = 3; i > 0; i--)
        stream << (int)bytes[i] << ".";
    
    stream << (int)bytes[0];
        

    return stream.str();
}


int Util::ipToInt(string ip)
{

    vector<string> tokens;
    Util::parseString(ip, tokens, '.');

    int value = (int)(pow(256, 3) * atoi(tokens.at(0).c_str())
                + pow(256, 2) * atoi(tokens.at(1).c_str())
                + 256 * atoi(tokens.at(2).c_str())
                + atoi(tokens.at(3).c_str())
                );


    return value;
}

