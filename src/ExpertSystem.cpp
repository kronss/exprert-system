#include "ExpertSystem.h"
#include "ESException.h"
#include "debug.h"
#include <iostream>
#include <sys/stat.h>


#include <iostream>
#include <cstdlib>
#include <unistd.h>


#define DEBUG 0

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

void ExpertSystem::printUsage(const char *pgmName)
{
	std::cout << "usage: " << pgmName << " [-v] <file>" << std::endl;
	std::cout << "       " << "-v     - verbose mode" << std::endl;
	std::cout << "       " << "<file> - file with all rules and initial facts" << std::endl;
}

inline
bool ExpertSystem::isRegularFile(const char *fileName)
{
    struct stat fileStat;

    memset(&fileStat, 0, sizeof(fileStat));
    stat(fileName, &fileStat);
    return !!S_ISREG(fileStat.st_mode);
}

void ExpertSystem::readInput(int ar, char **av)
{
    int c;

    //opterr = 0; /*verbose trace*/
    while ((c = getopt(ar, av, "v")) != -1)
    {
        switch (c)
        {
            case 'v':
            	verbose_ = true;
            	break;

            case '?':
            default:
            	goto usage;
        }
    }
	if(optind >= ar) {
		/* no filename arguments; */
    	goto usage;
	} else {
		/* process filename arguments */

		for(; optind < ar; optind++) {
			FILE *ifp = fopen(av[optind], "r");
			if(ifp == NULL) {
				fprintf(stderr, "can't open %s: %s\n",
					av[optind], strerror(errno));
				continue;
			}

			printf("processing %s\n", av[optind]);

			fclose(ifp);
		}
	}

//    std::cout << "optind = " << optind << std::endl;
//    std::cout << "ar = " << ar << std::endl;
//    std::cout << "av = " << av[ar - 1] << std::endl;

//    if (!av[ar - 1])
//    	goto usage;
//    fileName_ = av[ar - 1];

    debug("verbose is %d\n", verbose_);
    return;
usage:
	printUsage(av[0]);
	throw (ESException(PRINT_USAGE));
}




void ExpertSystem::init(int ar, char **av)
{

}



void ExpertSystem::usage()
{
	std::cerr << "" << std::endl;
}
