#include "ExpertSystem.h"
#include "ESException.h"
#include "debug.h"
#include <iostream>
#include <sys/stat.h>


#include <iostream>
#include <cstdlib>
#include <regex>
#include <fstream>


#include <unistd.h>
#include <string.h>
//#include <algorithm>


#define DEBUG 1

/******************************************************************************/
/* PUBLIC                                                                     */
/******************************************************************************/

void ExpertSystem::init(int ar, char **av)
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
        fileName_ = av[optind];
    }
    return;
usage:
	printUsage(av[0]);
	throw (ESException(PRINT_USAGE));
}

void ExpertSystem::readFromFile()
{
    std::fstream fs(fileName_);
    int lineNbr = 0;
    std::string line;


    DBG("File is %s", fileName_.c_str());

    if (!RegularFile(fileName_.c_str())) {
        DBG("Bad file");
        throw ESException(BAD_FILE, fileName_.c_str());
    }

    while (std::getline(fs, line)) {
        lineNbr++;
        removeUnusedCharacters(line);
        //std::cout << lineNbr << "|" << line << std::endl; //debug
        if (line.empty()) {
            continue;
        } else if (lineValid(line)) {
            //push rules;
        } else {
            throw ESException(BAD_FILE, fileName_.c_str());
        }
    }
}

/******************************************************************************/
/* PRIVATE                                                                    */
/******************************************************************************/

bool ExpertSystem::lineValid(std::string &line)
{
    std::smatch lineMatch;


//    std::regex emptyLineRegexp("^\\s*$");
    std::regex test("^[A-Z][A-Z]$");

    regex_search(line, lineMatch, test);

    if (regex_search(line, lineMatch, test)) {
        std::cout << "|" << line << std::endl; //debug
    }
//        std::cout << "|" << line << std::endl; //debug
//        std::cout << "-" << lineMatch << std::endl; //debug
//;
//    else if ()
//        ;
//    else if ()
//        ;
//    else
//        ;

    return true;//hack
}

void ExpertSystem::removeUnusedCharacters(std::string & line)
{
    if (line.find("#") != std::string::npos) {
        /*remove comments*/
        line.erase(line.find("#"));
    }

    /*remove whitespace characters*/
    line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
}


ExpertSystem::ExpertSystem() :
verbose_(false)
{
    DBG("Expert born");
}

ExpertSystem::~ExpertSystem()
{}

inline
bool ExpertSystem::RegularFile(const char *fileName)
{
    struct stat fileStat;

    memset(&fileStat, 0, sizeof(fileStat));
    DBG();
    if (stat(fileName, &fileStat)) return 0;
    DBG();
    return !!S_ISREG(fileStat.st_mode);
}

void ExpertSystem::usage()
{
	std::cerr << "" << std::endl;
}
