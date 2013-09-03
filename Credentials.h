/*
 * Credentials.h
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
 */

#ifndef CREDENTIALS_H_
#define CREDENTIALS_H_
#include <string>

using namespace std;

class Credentials {

	static Credentials* credentials;

	string userName;
	string password;
	string key;

	Credentials();
public:
	static Credentials* getCredentials();
	void populateCredentials(string fileName);

	string getUserName();
	string getPassword();
	string getKeyName();

	virtual ~Credentials();
};

#endif /* CREDENTIALS_H_ */
