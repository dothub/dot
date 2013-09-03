/*
 * Util.cpp
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
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

