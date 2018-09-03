#include "ExpertSystem.h"
#include "debug.h"

ExpertSystem& ExpertSystem::Instance()
{
    static ExpertSystem s;
    return s;
}
