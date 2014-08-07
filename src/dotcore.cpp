#include <cstdlib>
#include <signal.h>
#include <sstream>
#include "dotcore.h"
#include "console/console.h"
#include "executor/command_executor.h"
#include "global/global.h"



using namespace std;
using namespace console;
using namespace core;
using namespace executor;
using namespace global;


Console DOTCore::cons;

LoggerPtr DOTCore::logger = Logger::getLogger("DOTCore");


DOTCore:: DOTCore()
{
    LOG4CXX_INFO(logger, "In constructor");
}


void DOTCore::signalHandler(int signal)
{

    cons.stop();
}


void DOTCore::init()
{   
   
    LOG4CXX_INFO(logger, "Core Initiated");
          
    Global::dotRoot = CommandExecutor::executeLocal("pwd");
    LOG4CXX_DEBUG(logger, Global::dotRoot);
    
}



