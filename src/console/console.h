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
public:
    Console();
    static void signalHandler(int signal);
    static void start();
    static void stop();
    
};
}
#endif /*CONSOLE_H*/
