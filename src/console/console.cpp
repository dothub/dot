#include "console.h"
#include <iostream>
#include <cstdlib>
#include "../util/util.h"
#include "../infra/infra.h"
#include "../executor/command_executor.h"

using namespace executor;
using namespace console;
using namespace std;
using namespace util;
using namespace infra;

LoggerPtr Console::logger = Logger::getLogger("Console");

Console::Console()
{

    
}

void Console::signalHandler(int signal)
{
    LOG4CXX_DEBUG(logger, "Started signal handling");

    stop();
}

void Console::processInfraConfig(string& filename)
{

    Infra::load(filename);
}

void Console::connectVM(string& VM)
{

}

void Console::inputProcess(string& line)
{
    
    vector<string> tokens;
    bool invalid = false; 
    do
    {        
        Util::bipartiateString(line, tokens, ' ');
    
        for(int i = 0; i < tokens.size(); i++)
          LOG4CXX_DEBUG(logger, "Token: " << tokens[i]);
        
        if(!Util::onlySpaces(tokens[0]))
            break;

        else if(tokens[1].size() == 0 || Util::onlySpaces(tokens[1]))
        {
            invalid = true;
            break;
        }

        line = tokens[1];            
        tokens.clear();
    }while(true);

    if(!invalid)
    {
        LOG4CXX_DEBUG(logger, "Command: " << tokens[0]);

        if(tokens[0].compare("quit") == 0)
        {
            stop();
        }    
        else if(tokens[0].compare("load") == 0)
        {
           //Loading infrastructure conf file
            if(tokens[1].size() == 0 || Util::onlySpaces(tokens[1]))
                cout << "You have to specify the configuration file" << endl;
            else
            {
                LOG4CXX_DEBUG(logger, "Configuration File: " << tokens[1]);
                
                processInfraConfig(tokens[1]);
            } 
        }                            
        else if(tokens[0].compare("unload") == 0)
        {
           
        }                            
        else if(tokens[0].compare("deploy") == 0)
        {
            //loading emulation conf file/ known topology file
           
        }                            
        else if(tokens[0].compare("purge") == 0)
        {
           //purging emulation deployment
        }                            
        else if(tokens[0].compare("connect") == 0)
        {
            //open console of the the machine in a window
            connectVM(tokens[1]);
        }
        else if(tokens[0].compare("pingall") == 0)
        {
            //all pair wise ping between machines
           
        }                            
        else if(tokens[0].compare("ping") == 0)
        {
           //ping between only two machines
        }                            
        else if(tokens[0].compare("run") == 0)
        {
           //run shell commands in machines: parameter: ; separated list of machine and commands
        }                            
        else if(tokens[0].compare("detach") == 0)
        {
           //detach a switch to switch link
        }                            
        else if(tokens[0].compare("attach") == 0)
        {
            //attach previously detached switch to switch link
           
        }                            
        else if(tokens[0].compare("log") == 0)
        {
            //log {start, stop, show} 
            
            
        }      
        else if(tokens[0].compare("image") == 0)
        {
            //image snapshot
        }                      
        else if(tokens[0].compare("help")==0)
        {
            
        }
        else
            invalid = true;
     }
     if(invalid)
     {   
        invalid = false;
        cout << "Invalid command: write help" << endl;
     }
 
}
void Console::listen()
{
    string line;
    LOG4CXX_DEBUG(logger, "Console is listening");
    cout << "Welcome to DOT console..." << endl;
   
    while(true)
    {
        cout << "dot>";
        getline(cin, line);
        LOG4CXX_DEBUG(logger, "Line read: " << line);

        inputProcess(line);    
    }
 
}
void Console::start()
{
    LOG4CXX_INFO(logger, "Console is starting");
    listen();
   
}


void Console::stop()
{
    LOG4CXX_INFO(logger, "Stopping DOT Console");

    //TODO: Cleanup

    exit(0);
}


