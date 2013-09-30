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
 * Credentials.cpp
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
 */

#include "Credentials.h"
#include <iostream>
#include <fstream>
#include <map>
#include "Util.h"

Credentials* Credentials::credentials = NULL;

Credentials::Credentials() {

}

Credentials* Credentials::getCredentials() {

	if(credentials == NULL)
		credentials = new Credentials();
	return credentials;
}

void Credentials::populateCredentials(string fileName) {

	this->userName = "";
	this->password = "";
	this->key = "";

	ifstream fin(fileName.c_str());
	if(fin.is_open())
	{
		map<string, string> confMap;
		while(!fin.eof())
		{
			string line, key, value;
			fin >> line;

			Util::parseKeyValue(line, key, value, '=');

			confMap[key] = value;
		}

		fin.close();
		if(confMap.find("UserName") != confMap.end())
		{
			this->userName = confMap["UserName"];
		}
		else
			cout << "Please enter an user name in credential file: " << fileName <<  " with key: UserName" << endl;

		if(confMap.find("Password") != confMap.end())
		{
			this->password = confMap["Password"];
		}
		else if(confMap.find("KeyFile") != confMap.end())
		{
			this->key = confMap["KeyFile"];
		}
		else
			cout << "Please enter a password or public key information in: " << fileName <<  " with key: UserName or Key: KeyFile" << endl;
	}
	else
		cout << "Unable to open credential file: " << fileName << endl;
}

string Credentials::getUserName() {

	return this->userName;
}

string Credentials::getPassword() {
	return this->password;
}

string Credentials::getKeyName() {
	return this->key;
}

Credentials::~Credentials() {

}

