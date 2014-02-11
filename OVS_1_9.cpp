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
 * OVS_1_9.cpp
 *
 *  Created on: 2013-08-28
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "OVS_1_9.h"
#include <sstream>
#include <map>
#include <fstream>
#include <iostream>
#include "GREInterface.h"


using namespace std;

OVS_1_9::OVS_1_9(CommandExecutor* commandExec)
    :InstantitiateSwitch(commandExec)
{
    // TODO Auto-generated constructor stub

}

OVS_1_9::~OVS_1_9() {
    // TODO Auto-generated destructor stub
}

void OVS_1_9::clearSwitch(Switch* newSwitch) {

    ostringstream command;
    command << "sudo ovs-vsctl del-br " << newSwitch->getName();

    this->commandExec->executeRemote(newSwitch->getIPOfMachine(), command.str());

}

void OVS_1_9::runSwitch(Switch* newSwitch) {


    ostringstream fileName;
    fileName << "ovs_create_"<< newSwitch->getName() << ".sh";
    ofstream fout(fileName.str().c_str());

    if(fout.is_open())
    {
        fout << "sudo ovs-vsctl add-br " << newSwitch->getName() << endl;
        if(newSwitch->getIPofController().compare("")!=0)
        {
            fout << "sudo ovs-vsctl set-controller " << newSwitch->getName()
                        << " tcp:" << newSwitch->getIPofController() << ":" << newSwitch->getPortofController() << endl;
            fout << "sudo ovs-vsctl set-fail-mode " << newSwitch->getName() << " secure" << endl;
        }
        fout << "sudo ovs-vsctl set bridge " << newSwitch->getName() << " other-config:datapath-id=" << newSwitch->getDPID() << endl;

        fout.close();

        //cout << "now" << endl;
        this->commandExec->executeLocal("chmod +x "+fileName.str());
        //cout << "now2" << endl;
        this->commandExec->executeScriptRemote(newSwitch->getIPOfMachine(), "", fileName.str());


        /*if(remove(fileName.str().c_str()) != 0 )
            cout << "Error OVS Script file" << endl;*/

    }
    else
        cout << "Cannot create OVS Script file" << endl;


}

void OVS_1_9::attachPort(Switch* newSwitch, Interface* newInterface) {

    //hypervisor will create the tap interface
    ostringstream command;
    if(newInterface->getType() == VETH)
        command << "sudo ovs-vsctl add-port " << newSwitch->getName() << " " << newInterface->getName();
    else if(newInterface->getType() == GRE)
        command << " sudo ovs-vsctl add-port " << newSwitch->getName() << " " << newInterface->getName()
                    << " -- set interface " <<  newInterface->getName()
                    << " type=gre options:remote_ip=" << ((GRE_Interface*)newInterface)->getRemoteIP() << " options:key=flow";

    //cout << command.str() << endl;
    this->commandExec->executeRemote(newSwitch->getIPOfMachine(), command.str());

}

string OVS_1_9::createClearAllRules(Switch* newSwitch) {
    ostringstream command;
    command << "sudo ovs-ofctl del-flows " << newSwitch->getName();

    return command.str();
}

string OVS_1_9::createStaticTunnelRule(Switch* newSwitch,
        unsigned int tunnel_id, unsigned int input_port,
        unsigned int output_port) {

    ostringstream command;
    command << "sudo ovs-ofctl add-flow " << newSwitch->getName()
            << " in_port=" << input_port << ",actions=set_tunnel:"<< tunnel_id << ",output:" << output_port << endl;
    command << "sudo ovs-ofctl add-flow " << newSwitch->getName()
            << " in_port=" << output_port << ",tun_id=" << tunnel_id << ",actions=output:" << input_port;
    return command.str();
}

void OVS_1_9::assignPortNumber(Switch* newSwitch, Interface* newInterface) {

    ostringstream command;
    command << "sudo ovs-ofctl show " << newSwitch->getName() << "| grep " << newInterface->getName() << "|cut -f1 -d'('|cut -f2 -d' '";
    string portNumber = this->commandExec->executeRemote(newSwitch->getIPOfMachine(), command.str());

    stringstream strStream(portNumber);
    strStream >> newInterface->port;

}

void OVS_1_9::assignStaticTunnelRule(Switch* newSwitch,
        list<pair<unsigned int, pair<unsigned int, unsigned int> > > rules) {

        ostringstream fileName;
        fileName << "ovs_static_"<< newSwitch->getName() << ".sh";
        ofstream fout(fileName.str().c_str());

        if(fout.is_open())
        {
            fout << this->createClearAllRules(newSwitch) << endl;

            for(list<pair<unsigned int, pair<unsigned int, unsigned int> > >::iterator iter = rules.begin();
                        iter != rules.end(); iter++)
            {
                fout << this->createStaticTunnelRule(newSwitch, iter->first, iter->second.first, iter->second.second) << endl;
            }


            fout.close();

            this->commandExec->executeLocal("chmod +x "+fileName.str());
            this->commandExec->executeScriptRemote(newSwitch->getIPOfMachine(), "", fileName.str());

            /*if(remove(fileName.str().c_str()) != 0 )
                cout << "Error OVS Static file" << endl;
               */
        }
        else
            cout << "Cannot create OVS Static Rule file" << endl;



}

void OVS_1_9::clearAllRules(Switch* newSwitch) {

    string command = this->createClearAllRules(newSwitch);
    this->commandExec->executeRemote(newSwitch->getIPOfMachine(), command);
}





