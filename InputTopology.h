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
