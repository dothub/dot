/*
 * Mapping.h
 *
 *  Created on: 2013-08-07
 *      Author: ar3roy
 */

#ifndef MAPPING_H_
#define MAPPING_H_
#include "PartitioningAlgorithm.h"
#include <string>
#include <vector>

using namespace std;

class PartitioningAlgorithm;

class Mapping {

	Mapping();
	static Mapping* mapping;

	vector<string> switch2machine;

	void instertMapping(string machine);

	friend class PartitioningAlgorithm;

public:
	static Mapping* getMapping();

	string getMachine(unsigned long switchID);

	virtual ~Mapping();


};

#endif /* MAPPING_H_ */
