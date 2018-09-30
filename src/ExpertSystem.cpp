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

    /*line without unused characters*/
    while (std::getline(fs, line)) {
        lineNbr++;
        removeUnusedCharacters(line);
        //std::cout << lineNbr << "|" << line << std::endl; //debug
        if (line.empty()) {
            continue;
        } else if (lineInitFacts(line)) {
            readInitFacts(line);
        } else if (lineQueryFacts(line)) {
            readQueryFacts(line);
        } else if (lineValid(line)) {
            //push rules;
            createRule(line);
        } else {
            throw ESException(BAD_FILE, fileName_.c_str());
        }
    }
}

/******************************************************************************/
/* PRIVATE                                                                    */
/******************************************************************************/

void ExpertSystem::createRule(std::string &line)
{
    std::smatch lineMatch;
                     /*(   1st    )( 2nd  )(   3rd    )                */
    std::regex test4("^([A-Z!+|^]*)(<=>|=>)([A-Z!+|^]*)$"); /*tokenyzer*/
    std::string tmp;
    regex_search(line, lineMatch, test4);

    std::cout << "    ----0st: " << lineMatch[0].str() << std::endl;
    std::cout << "    ----1st: " << lineMatch[1].str() << std::endl;
    std::cout << "    ----2st: " << lineMatch[2].str() << std::endl;
    std::cout << "    ----3st: " << lineMatch[3].str() << std::endl;

    /*check rules*/

    if (lineMatch[2].str() == "<=>")
        throw ESException(NOT_SUPPORTED, lineMatch[2].str());

    if () {

    }





}

bool ExpertSystem::lineInitFacts(std::string &line)
{
    bool ret = false;
    //    std::regex test1("(^=[A-Z]{0,26}$)");




    return ret;
}

bool ExpertSystem::lineValid(std::string &line)
{
    std::smatch lineMatch;

//    std::regex emptyLineRegexp("^\\s*$");
//    std::regex test("^(!?[A-Z])(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$");
//    std::regex test("^(!?[A-Z]\\+|\\||\\^!?[A-Z]*)(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$");
//    std::regex test2("^\\?[A-Z]{0,26}$");

//v1
    std::regex test1("^(!?[A-Z])(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$"); //    Для тех где слева одна буква
    std::regex test2("^(!?[A-Z](\\+!?[A-Z])+)(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$"); // Для плюсов
    std::regex test3("^(!?[A-Z](\\+|\\||\\^)!?[A-Z])(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$"); // Для других операций



    if        (regex_search(line, lineMatch, test1)) {
        std::cout << "OK1: " << line << std::endl; //debug
    } else if (regex_search(line, lineMatch, test2)) {
        std::cout << "OK2: " << line << std::endl; //debug
    } else if (regex_search(line, lineMatch, test3)) {
        std::cout << "OK3: " << line << std::endl; //debug
    } else {
        std::cout << "KO: " << line << std::endl; //debug
//        throw ESException(INVAL_TOKEN, line); /*TODO: uncoment*/
        goto done; /*TODO: remove hack*/
    }


    std::cout << "    0st: " << lineMatch[0].str() << std::endl;
    std::cout << "    1st: " << lineMatch[1].str() << std::endl;
    std::cout << "    2st: " << lineMatch[2].str() << std::endl;
    std::cout << "    3st: " << lineMatch[3].str() << std::endl;
    std::cout << "    4st: " << lineMatch[4].str() << std::endl;
    std::cout << "    5st: " << lineMatch[5].str() << std::endl;


done: /*TODO: remove hack*/
    return ALWAYSTRUE;
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
