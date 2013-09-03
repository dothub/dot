/*
 * PartitionAnalyzer.h
 *
 *  Created on: 2013-08-23
 *      Author: ar3roy
 */

#ifndef PARTITIONANALYZER_H_
#define PARTITIONANALYZER_H_
#include "PhysicalMachines.h"
#include "Mapping.h"
#include "InputTopology.h"

class PartitionAnalyzer {
public:
	PartitionAnalyzer(PhysicalMachines* machine, Mapping* mapping, InputTopology* topology);
	virtual ~PartitionAnalyzer();
};

#endif /* PARTITIONANALYZER_H_ */
