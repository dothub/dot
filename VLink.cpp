/*
 * VLink.cpp
 *
 *  Created on: 2013-08-28
 *      Author: ar3roy
 */

#include "VLink.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

VLink::VLink(CommandExecutor* commandExec):
	InstantitiateLink(commandExec){


}

VLink::~VLink() {
	// TODO Auto-generated destructor stub
}

void VLink::createLink(Link* newLink) {

	ostringstream fileName;
	fileName << "link_create"<< newLink->getId() << ".sh";
	ofstream fout(fileName.str().c_str());


	if(fout.is_open())
	{
		fout << "sudo ip link del dev " << newLink->getInterface1()->getName()
				<< " type veth peer name " << newLink->getInterface2()->getName() << endl;

		fout << "sudo ip link add name " << newLink->getInterface1()->getName()
						<< " type veth peer name " << newLink->getInterface2()->getName() << endl;

		fout << "sudo ifconfig " << newLink->getInterface1()->getName() << " up" << endl;
		fout << "sudo ifconfig " << newLink->getInterface2()->getName() << " up" << endl;
		fout << "sudo tc qdisc add dev " << newLink->getInterface1()->getName()
				<<  " root netem delay " << newLink->getDelay() << "ms" << endl;

		fout.close();


		this->commandExec->executeLocal("chmod +x "+ fileName.str());
		this->commandExec->executeScriptRemote(newLink->getInterface1()->getSwitch()->getIPOfMachine(), "", fileName.str());

		if(remove(fileName.str().c_str()) != 0 )
			cout << "Error Link Script file" << endl;
	}
	else
		cout << "Cannot create Link Script file" << endl;

}


