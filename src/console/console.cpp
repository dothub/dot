#include "console.h"
#include <iostream>
#include <cstdlib>
#include "../util/util.h"

using namespace console;
using namespace std;
using namespace util;

LoggerPtr Console::logger = Logger::getLogger("Console");

Console::Console()
{

    
}

void Console::signalHandler(int signal)
{
    LOG4CXX_DEBUG(logger, "Started signal handling");

    stop();
}


void Console::start()
{
    LOG4CXX_INFO(logger, "Console is starting");
    
    string line;
    bool invalid = false;

    cout << "Welcome to DOT console..." << endl;
   
     while(true)
    {
        cout << "dot>";
        getline(cin, line);
        LOG4CXX_DEBUG(logger, "Line read: " << line);
        
        vector<string> tokens;
        Util::parseString(line, tokens, ' ');
    
        for(int i = 0; i < tokens.size(); i++)
            LOG4CXX_DEBUG(logger, "Token: " << tokens[i]);

        for(int i = 0; i < tokens.size(); i++)
        {
            if(!Util::onlySpaces(tokens[i]))
            {
                LOG4CXX_DEBUG(logger, "Command: " << tokens[i]);

                if(tokens[i].compare("quit") == 0)
                {
                    stop();
                }                
                else
                {   
                    invalid = true;
                    break;
                }
            }
        }

        if(invalid == true)
        {
             invalid = false;
             cout << "Invalid command: write help" << endl;
        }
    }
    
}


void Console::stop()
{
    LOG4CXX_INFO(logger, "Stopping DOT Console");

    //TODO: Cleanup

    exit(0);
}


