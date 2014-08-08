#ifndef CONSOLE_H
#define CONSOLE_H

#include <log4cxx/logger.h>
#include "../core/dotcore.h"
#include "../global/global.h"

using namespace log4cxx;
namespace console
{

class Console
{
  
    static LoggerPtr logger;
    static void stop();
    static void listen();
    static void inputProcess(string& line); 
    static void processInfraConfig(string& filename);
    static void connectVM(string& VM);
public:
    Console();
    static void signalHandler(int signal);
    static void start();
   
};
}
#endif /*CONSOLE_H*/
