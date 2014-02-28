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
 * VLink.cpp
 *
 *  Created on: 2013-08-28
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "VLink.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

VLink::VLink(CommandExecutor* commandExec):
    AbstractLink(commandExec){


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

        this->commandExec->executeRemote(newLink->getInterface1()->getSwitch()->getIPOfMachine(), "rm " + fileName.str());

        if(remove(fileName.str().c_str()) != 0 )
            cout << "Error Link Script file" << endl;
    }
    else
        cout << "Cannot create Link Script file" << endl;

}


