#ifndef DOTCORE_H
#define DOTCORE_H

#include "console/console.h"
#include "global/global.h"

using namespace console;

namespace core
{

class DOTCore
{   
 
   bool debugMode;
   
   static Console* cons;
   
public:
        DOTCore(bool debug=false);
        static void signalHandler(int signal);
        void setDebug(bool mode);
};

}
#endif /*DOTCORE_H*/
