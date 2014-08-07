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
    LOG4CXX_DEBUG(logger, "In constructor");
}


void DOTCore::signalHandler(int signal)
{
    LOG4CXX_INFO(logger, "Started signal handling");

    cons.stop();
}


void DOTCore::init()
{   
   
    LOG4CXX_INFO(logger, "Core Initiation Started");
          
    Global::dotRoot = CommandExecutor::executeLocal("pwd");
    LOG4CXX_DEBUG(logger, "Dot Root: " << Global::dotRoot);


    LOG4CXX_INFO(logger, "Core initiation finised");
    
}



