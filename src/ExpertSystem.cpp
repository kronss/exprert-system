#include "ExpertSystem.h"
#include "debug.h"

ExpertSystem::ExpertSystem()
{}

ExpertSystem::~ExpertSystem()
{}


ExpertSystem& ExpertSystem::Instance()
{
    static ExpertSystem s;
    return s;
}
