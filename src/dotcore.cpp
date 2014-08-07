#include <cstdlib>
#include <signal.h>
#include "dotcore.h"
#include "console/console.h"

using namespace console;
using namespace core;


Console* DOTCore::cons = NULL;

DOTCore:: DOTCore(bool debug):debugMode(debug)
{
    cons = new Console();
}


void DOTCore::signalHandler(int signal)
{

    if(cons != NULL)
        cons->stop();
}

void DOTCore::setDebug(bool mode)
{
    debugMode = true;
}

