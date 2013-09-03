/*
 * PartitioningAlgorithm.h
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
 */

#ifndef PARTITIONINGALGORITHM_H_
#define PARTITIONINGALGORITHM_H_
#include <string>
#include "Mapping.h"

using namespace std;

class Mapping;
class PartitioningAlgorithm {
protected:
	void instertMapping(Mapping* mapping, string machine);
public:
	PartitioningAlgorithm();
	virtual ~PartitioningAlgorithm();
	virtual void run() = 0;
};

#endif /* PARTITIONINGALGORITHM_H_ */
