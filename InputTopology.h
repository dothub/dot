/*
 * LogicalTopology.h
 *
 *  Created on: 2013-08-06
 *      Author: ar3roy
 */

#ifndef INPUTTOPOLOGY_H_
#define INPUTTOPOLOGY_H_

#include <string>
using namespace std;

class InputTopology {

	struct LinkProperty
	{
		double bandwidth;
		double delay;

		LinkProperty():bandwidth(0),delay(0){}
	};

	LinkProperty ** topology;

	static InputTopology* inputTopology;
	unsigned long numberOfSwitches;

	InputTopology();

public:
	static InputTopology* getInputTopology();

	void populateTopology(string fileName);


	unsigned long getNumberOfSwitches();
	void populateTopologyBandwidth(double ** & topologyBandwidth);
	void populateTopologyDelay(double ** & topologyDelay);

	double getLinkDelay(unsigned long switch1, unsigned long switch2);
	double getLinkBandwidth(unsigned long switch1, unsigned long switch2);

	bool isNeighbor(unsigned long switch1, unsigned long switch2);

	virtual ~InputTopology();
};

#endif /* INPUTTOPOLOGY_H_ */
