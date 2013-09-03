/*
 * Hosts.h
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
 */

#ifndef HOSTS_H_
#define HOSTS_H_

#include <string>
#include <vector>
using namespace std;

class Hosts {
	struct HostAttribute
	{
		unsigned long host_id;
		unsigned long switch_id;
		string mac;
		string ip;
		unsigned int cpu;
	};
	static Hosts* hosts;
	Hosts();

	unsigned long numberOfHosts;
	vector<HostAttribute > hostIdVector;

public:
	static Hosts* getHosts();
	void populateHosts(string fileName);

	unsigned long getNumberOfHosts();

	unsigned long getSwitch(unsigned long hostId);
	string getMacAddress(unsigned long hostId);
	string getIPAddress(unsigned long hostId);
	unsigned int getCPU(unsigned long hostId);

	virtual ~Hosts();
};

#endif /* HOSTS_H_ */
