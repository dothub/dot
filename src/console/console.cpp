#include "console.h"

using namespace console;


LoggerPtr Console::logger = Logger::getLogger("Console");

Console::Console()
{

}

void Console::start()
{

}


void Console::stop()
{
    LOG4CXX_INFO(logger, "Stopping");    
}


