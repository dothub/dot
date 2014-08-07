#ifndef DOTCORE_H
#define DOTCORE_H

#include "console/console.h"
#include "global/global.h"
#include <log4cxx/logger.h>

using namespace log4cxx;
using namespace console;


namespace core
{

class DOTCore
{   
 
    static LoggerPtr logger; 
   
    static Console cons;
   
public:
        DOTCore();
        static void signalHandler(int signal);
        void init();
        
};

}
#endif /*DOTCORE_H*/
