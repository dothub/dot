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
 * 
 *  CreateConf.cpp
 *  Created on: 2014-02-13
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include "Util.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <utility>


using std::map;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream; 
using std::getline;
using std::fstream;

void processConfFile(string fileName)
{

    string emulationName;
    string directory = "./emulations/";
    string baseIP= "10.254.0.0";
    
    string defaultConfFileName = "DefaultConfiguration_";
    string physicalTopologyFileName = "PhysicalTopology_";
    string physicalTopologyDelayFileName = "PhysicalTopologyDelay_";
    string logicalTopologyFileName = "LogicalTopology_";
    string controllerFileName = "ControllerInfo_";
    string switch2ControllerFileName = "Switch2Controller_";
    string hostConfigurationFileName = "HostInfo_";
    string hypervisorConfFileName = "Hypervisor_";
    string credentialFileName = "CredentialFile_";

    ifstream fin(fileName.c_str());
   
    ofstream fout_DefaultConf;
    ofstream fout_PhysicalTopo;
    ofstream fout_PhysicalTopoDelay;
    ofstream fout_LogicalTopo;
    ofstream fout_Ctrl;
    ofstream fout_Sw2Ctrl;
    ofstream fout_Host;
    ofstream fout_Hypervisor;
    ofstream fout_Credential;
 
    

    vector<string> physicalMachines;
    map<pair<string, string>, double> physicalMachineDelayMap;


    if(fin.is_open())
    {
        while(!fin.eof())
        {
            string line;
            
            getline(fin, line);
            
            //Skipping the comments and empty lines between sections
            if(line.size() == 0 || line[0] == '#')
                continue;

            else if(line.substr(0,strlen("[EmulationName]")).compare("[EmulationName]") == 0)
            {
               
                //reading the emulation name by skipping any empty line or comment    
                fin >> line;
                while(line.size() == 0 || line[0] == '#')
                    fin >> line;
                
                emulationName = line;
                directory += line;
                directory += "/";

                string storingPath = "mkdir -p ./emulations/";
                storingPath += line;
                storingPath += "/";

                system(storingPath.c_str());
                
                storingPath = "./emulations/";
                storingPath += line;
                storingPath += "/";

                //storingPath="";
                string defaultConfFileNameWithPath = storingPath + defaultConfFileName + emulationName;
                string physicalTopologyFileNameWithPath =  storingPath + physicalTopologyFileName + emulationName;
                string physicalTopologyDelayFileNameWithPath =  storingPath + physicalTopologyDelayFileName + emulationName;
                string logicalTopologyFileNameWithPath =  storingPath + logicalTopologyFileName + emulationName;
                string controllerFileNameWithPath =  storingPath + controllerFileName + emulationName;
                string switch2ControllerFileNameWithPath =  storingPath + switch2ControllerFileName + emulationName;
                string hostConfigurationFileNameWithPath =  storingPath + hostConfigurationFileName + emulationName;
                string hypervisorConfFileNameWithPath =  storingPath + hypervisorConfFileName + emulationName;
                string credentialFileNameWithPath = storingPath + credentialFileName + emulationName;
                               

                fout_DefaultConf.open(defaultConfFileNameWithPath.c_str(), ofstream::out );
                fout_PhysicalTopo.open(physicalTopologyFileNameWithPath.c_str(), ofstream::out);
                fout_PhysicalTopoDelay.open(physicalTopologyDelayFileNameWithPath.c_str(), ofstream::out);
                fout_LogicalTopo.open(logicalTopologyFileNameWithPath.c_str(), ofstream::out);
                fout_Ctrl.open(controllerFileNameWithPath.c_str(), ofstream::out);
                fout_Sw2Ctrl.open(switch2ControllerFileNameWithPath.c_str(), ofstream::out);
                fout_Host.open(hostConfigurationFileNameWithPath.c_str(), ofstream::out);
                fout_Hypervisor.open(hypervisorConfFileNameWithPath.c_str(), ofstream::out);
                fout_Credential.open(credentialFileNameWithPath.c_str(), ofstream::out);

                if( !fout_DefaultConf.is_open() || !fout_PhysicalTopo.is_open()
                    || !fout_PhysicalTopoDelay.is_open() || !fout_LogicalTopo.is_open()
                    || !fout_Ctrl.is_open() || !fout_Sw2Ctrl.is_open()
                    || !fout_Host.is_open() || !fout_Hypervisor.is_open()
                    || !fout_Credential.is_open()
                    )       
                {
                    cout <<  "Any one of the otuput file cannot be opened" << endl;
                    exit(1);
                }

            }


            else if(line.substr(0,strlen("[PhysicalTopology]")).compare("[PhysicalTopology]") == 0)
            {
                
                //reading the emulation name by skipping any empty line or comment    
                getline(fin, line);
                cout << line << endl;
                while(line.size() == 0 || line[0] == '#')
                {
                    getline(fin, line);
                    cout << line;
                }
                
                cout << "PT: " << line << endl;
                //Getting the number of physical machines
                int numberOfPhysicalMachine = atoi(line.c_str());
                fout_PhysicalTopo << numberOfPhysicalMachine-1 << endl;
                
                for(int i = 0; i < numberOfPhysicalMachine; i++)
                {
                    getline(fin, line);
                    vector<string>*tokens;
                    Util::parseString(line, tokens, ' ');
                    
                    cout << tokens->at(0) << endl;
                    if(tokens->at(0).compare("manager") == 0)
                    {
                        fout_DefaultConf << "MasterName=" << tokens->at(1) << endl;
                        fout_DefaultConf << "MasterIP=" << tokens->at(2) << endl;
                    }
                    else if(tokens->at(0).compare("node") == 0)
                    {
                        physicalMachines.push_back(tokens->at(1));
                        
                        fout_PhysicalTopo << tokens->at(1) << " " << tokens->at(2) 
                            << " " << tokens->at(3) << " " << tokens->at(4) 
                            << " " << tokens->at(5) << " " << tokens->at(6) 
                            << " " << tokens->at(7) << endl;
                    }
               
                }

                fout_DefaultConf << "PhysicalTopology=" << directory << physicalTopologyFileName << emulationName << endl;                
            }


            else if(line.substr(0,strlen("[PhysicalTopologyDelay]")).compare("[PhysicalTopologyDelay]") == 0)
            {
                //reading the emulation name by skipping any empty line or comment    
                getline(fin, line);
                cout << line << endl;
                while(line.size() == 0 || line[0] == '#')
                {
                    getline(fin, line);
                    cout << line;
                }
                
                cout << "PTD: " << line << endl;

                int numberOfPhysicalMachineDelay = atoi(line.c_str());

                if(numberOfPhysicalMachineDelay == 0 || physicalMachines.size() == 1)
                {
                    fout_DefaultConf << "PhysicalMachineDelay=No" << endl;
                }
                else
                {
                    fout_DefaultConf << "PhysicalMachineDelay=Yes" << endl;
                    fout_DefaultConf << "PhysicalDelayFile=" <<   directory <<  physicalTopologyDelayFileName << emulationName << endl;


                    for(int i = 0; i < numberOfPhysicalMachineDelay; i++)
                    {
                        getline(fin, line);
                        vector<string>*tokens;
                        Util::parseString(line, tokens, ' ');
                        
                        cout << tokens->at(0) << endl;
                        
                        physicalMachineDelayMap.insert(make_pair(make_pair(tokens->at(0), tokens->at(1)),
                                                           atof(tokens->at(2).c_str())));

                    }
                        
                    int pairwiseLinks = 0;
      
                    for(int i = 0; i < physicalMachines.size()-1; i++)
                    {
                        for(int j = i+1; j < physicalMachines.size(); j++)
                        {
                            pairwiseLinks ++;

                            if(physicalMachineDelayMap.find(make_pair(physicalMachines[i], physicalMachines[j])) 
                                            == physicalMachineDelayMap.end() 
                                && 
                                physicalMachineDelayMap.find(make_pair(physicalMachines[j], physicalMachines[i])) 
                                                     == physicalMachineDelayMap.end()
                                )
                            
                                physicalMachineDelayMap.insert(make_pair(make_pair(physicalMachines[i], physicalMachines[j]),
                                                                0));
                        
                        }
                    }
                
                    fout_PhysicalTopoDelay << pairwiseLinks << endl;

                    for(map< pair<string, string>, double>::iterator iter1 = physicalMachineDelayMap.begin();
                            iter1 != physicalMachineDelayMap.end(); iter1++)
                        fout_PhysicalTopoDelay << iter1->first.first << " " << iter1->first.second << " " << iter1->second << endl;
                    
                    
                }
                
            }
            
            else if(line.substr(0,strlen("[LogicalTopology]")).compare("[LogicalTopology]") == 0)
            {
                //reading the emulation name by skipping any empty line or comment    
                getline(fin, line);
                cout << line << endl;
                while(line.size() == 0 || line[0] == '#')
                {
                    getline(fin, line);
                    cout << line;
                }
                
                fout_DefaultConf << "LogicalTopology=" << directory << logicalTopologyFileName << emulationName << endl;

                cout << "LT: " << line << endl;
                vector<string>*tokens;
                Util::parseString(line, tokens, ' ');

                fout_LogicalTopo << line << endl;
                for(int i = 0; i < atoi(tokens->at(1).c_str()); i++)
                {
                    getline(fin,line);
                    fout_LogicalTopo << line << endl;
                }
            }
            
            else if(line.substr(0,strlen("[VirtualMachineProvision]")).compare("[VirtualMachineProvision]") == 0)
            {
                //reading the emulation name by skipping any empty line or comment    
                getline(fin, line);
                cout << line << endl;
                while(line.size() == 0 || line[0] == '#')
                {
                    getline(fin, line);
                    cout << line;
                }

                fout_DefaultConf << "HyperVisorConfiguration" <<  "=" <<  directory 
                        << hypervisorConfFileName << emulationName << endl;

                cout << "VMP: " << line << endl;
                while(line[0] != '#')
                {
                    vector<string>*tokens;
                    Util::parseString(line, tokens, '=');

                    if(tokens->at(0).compare("Hypervisor") == 0)
                    {
                        fout_Hypervisor << "virt_type=" << tokens->at(1) << endl;
                    }

                    else if(tokens->at(0).compare("Library") == 0)
                    {
                        fout_DefaultConf << "HyperVisor=" << tokens->at(1) << endl;
                    }

                    else if(tokens->at(0).compare("ImageLocation") == 0)
                    {
                        fout_DefaultConf << "HostImage=" << tokens->at(1) << endl;

                    }
                    else if(tokens->at(0).compare("NetworkFile") == 0)
                    {
                        fout_Hypervisor << "networkFile=" << tokens->at(1) << endl;
                    }
                    getline(fin, line);
                }

            }
            
            else if(line.substr(0,strlen("[VirtualMachines]")).compare("[VirtualMachines]") == 0)
            {
                //reading the emulation name by skipping any empty line or comment    
                getline(fin, line);
                cout << line << endl;
                while(line.size() == 0 || line[0] == '#')
                {
                    getline(fin, line);
                    cout << line;
                }

                fout_DefaultConf << "HostConfiguration" <<  "=" <<  directory 
                        << hostConfigurationFileName << emulationName << endl;

                cout << "VM: " << line << endl;
                int numberOfVMs = atoi(line.c_str());
            
                fout_Host << line << endl;

                for(int i = 0; i < numberOfVMs; i++)
                {
                    getline(fin, line);

                    vector<string>*tokens;
                    Util::parseString(line, tokens, ' ');

                    int hostID = atoi(tokens->at(0).substr(1).c_str());
                    
                    string mac = Util::intToMac(hostID);
                    cout << mac << endl;
                    
                    string ip = Util::intToIP(Util::ipToInt(baseIP) + hostID);
                    cout << ip << endl;
                    
                    fout_Host << tokens->at(0) << " " << tokens->at(1) << " "
                            << mac << " " << ip << " " << tokens->at(2) << " "
                            << tokens->at(3) << endl;

                }

            }
            
            else if(line.substr(0,strlen("[Controllers]")).compare("[Controllers]") == 0)
            {
                //reading the emulation name by skipping any empty line or comment    
                getline(fin, line);
                cout << line << endl;
                while(line.size() == 0 || line[0] == '#')
                {
                    getline(fin, line);
                    cout << line;
                }

                fout_DefaultConf << "Controllers" <<  "=" <<  directory
                        << controllerFileName << emulationName << endl;

                cout << "CT: " << line << endl;

                fout_Ctrl << line << endl;
                
                int numberOfControllers = atoi(line.c_str());

                for(int i = 0; i < numberOfControllers; i++)
                {
                    getline(fin,line);
                    fout_Ctrl << line << endl;
                }


            }
            
            else if(line.substr(0,strlen("[Switch2Controller]")).compare("[Switch2Controller]") == 0)
            {
                //reading the emulation name by skipping any empty line or comment    
                getline(fin, line);
                cout << line << endl;
                while(line.size() == 0 || line[0] == '#')
                {
                    getline(fin, line);
                    cout << line;
                }

                fout_DefaultConf << "SwitchToController" <<  "=" <<  directory
                        << switch2ControllerFileName << emulationName << endl;

                cout << "S2C: " << line << endl;

                fout_Sw2Ctrl << line << endl;
                int numberOfSwitches = atoi(line.c_str());

                for(int i = 0; i < numberOfSwitches; i++)
                {
                    getline(fin,line);
                    fout_Sw2Ctrl << line << endl;
                }

            }
            
            else if(line.substr(0,strlen("[Credentials]")).compare("[Credentials]") == 0)
            {
                //reading the emulation name by skipping any empty line or comment    
                getline(fin, line);
                cout << line << endl;
                while(line.size() == 0 || line[0] == '#')
                {
                    getline(fin, line);
                    cout << line;
                }

                fout_DefaultConf << "UserCredentials" <<  "=" <<  directory
                        << credentialFileName << emulationName << endl;

                cout << "CRE: " << line << endl;

                fout_Credential << line << endl;

            }
            
            else if(line.substr(0,strlen("[Embedding]")).compare("[Embedding]") == 0)
            {
                //Currently assigned to default value
                fout_DefaultConf << "EmbeddingAlgorithm=Guaranteed_Embedding" << endl
                                 << "EmbeddingAlgorithmConfiguration=Guaranteed_Embedding_Conf" << endl;
            }

            
        }

        fin.close();
        fout_DefaultConf.close();
        fout_PhysicalTopo.close();
        fout_PhysicalTopoDelay.close();
        fout_LogicalTopo.close();
        fout_Ctrl.close();
        fout_Sw2Ctrl.close();
        fout_Host.close();
        fout_Hypervisor.close();
        fout_Credential.close();
        
    }
    else
        cout << "Unable to open configuration file: " << fileName <<  endl;
}


int main(int argc, char * argv[])
{

    string confFileName;
    
    if(argc == 3 && strcmp(argv[1],"-c") == 0)
            confFileName = argv[2];
   
    else
    {
        cout << "-h help" << endl <<
            "-c conf_file_name" << endl;
        exit(0);
    }
    
    processConfFile(confFileName);  

    return 0;
}
