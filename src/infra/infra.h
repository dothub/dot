#ifndef INFRA_H
#define INFRA_H
#include <iostream>
#include <log4cxx/logger.h>

using namespace log4cxx;
using namespace std;

namespace infra
{

class Infra{

    static LoggerPtr logger;

public:
    static void load(string& fileName);
    static void unload();
};

}
#endif /*INFRA_H*/
