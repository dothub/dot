#ifndef DOTCORE_H
#define DOTCORE_H


#include "../global/global.h"
#include <log4cxx/logger.h>

using namespace log4cxx;


namespace core
{

class DOTCore
{   
 
    static LoggerPtr logger; 
   
   
public:
        DOTCore();
        static void init();
        
};

}
#endif /*DOTCORE_H*/
