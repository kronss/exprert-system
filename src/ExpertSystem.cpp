#include "ExpertSystem.h"
#include "debug.h"
#include <iostream>
#include <sys/stat.h>


#include <iostream>
#include <cstdlib>
#include <unistd.h>


#define DEBUG 1

ExpertSystem::ExpertSystem() :
verbose_(false)
{
	debug("Expert born\n");
}

ExpertSystem::~ExpertSystem()
{}

ExpertSystem& ExpertSystem::Instance()
{
    static ExpertSystem s;
    return s;
}

inline
bool ExpertSystem::is_regular_file(const char *fileName)
{
    struct stat fileStat;

    memset(&fileStat, 0, sizeof(fileStat));
    stat(fileName, &fileStat);
    return !!S_ISREG(fileStat.st_mode);
}

void ExpertSystem::readInput(int ar, char **av)
{
    const char* nvalue = "World" ;
    int tvalue = 1 ;

    int c ;
//    ar = (char * const *)ar;
    while ((c = getopt(ar, av, "v")) != -1)
    {
        switch(c)
        {
            case 'v':
            	verbose_ = true;
                break;
        }
    }
    debug("verbose is %d\n", verbose_);
}




void ExpertSystem::init(int ar, char **av)
{

}



void ExpertSystem::usage()
{
	std::cerr << "" << std::endl;
}
