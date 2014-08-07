#ifndef CONSOLE_H
#define CONSOLE_H

#include <log4cxx/logger.h>
using namespace log4cxx;
namespace console
{

class Console
{

    static LoggerPtr logger;
public:
    Console();
    void start();
    void stop();
    
};
}
#endif /*CONSOLE_H*/
