#include "infra.h"

using namespace infra;

LoggerPtr Infra::logger = Logger::getLogger("Infra");


void Infra::load(string& filename)
{
    LOG4CXX_DEBUG(logger, "Filename: " << filename);
}

void Infra::unload()
{
    LOG4CXX_DEBUG(logger, "Unloading infrastructure");

}
