/*
 * Util.h
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
 */

#ifndef UTIL_H_
#define UTIL_H_
#include <string>
#include <vector>

using namespace std;

class Util {
public:
	void static parseKeyValue(string input, string& key, string& value, char delimeter);
	void static parseString(string input, vector<string>* &tokens, char delimeter);
	string static intToHexString(unsigned long input, unsigned int width=0);
	string static getFileName(const string& strPath);
	string static getPathName(const string& strPath);
};

#endif /* UTIL_H_ */
