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

        std::cout << lineNbr << ". " << line << std::endl; //debug
        if (line.empty()) {
            continue ;
        } else if (lineInitFacts(line)) {
        	//change state PC
        } else if (lineQueryFacts(line)) {
        	//change state PC
        } else if (lineValid(line)) {
            //push rules;
//        	std::cout << lineNbr << ". dick" << std::endl; //debug
            createRule(line);
        } else {
        	continue;
//        	std::cout << lineNbr << ". dick" << std::endl; //debug
//            throw ESException(BAD_FILE, fileName_.c_str()); //TODO: rework this
        }
    }

    std::cout << "------------------------------------" << std::endl;
    for (auto const& i : RulesList_) {
        std::cout << i.getLeft() << std::endl;
        std::cout << i.getInference() << std::endl;
        std::cout << i.getRight() << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }






}

/******************************************************************************/
/* PRIVATE                                                                    */
/******************************************************************************/

void ExpertSystem::createRule(std::string &line)
{
    std::smatch lineMatch;
                     /*(   1st    )( 2nd  )(   3rd    )*/
    std::regex test4("^([A-Z!+|^]*)(<=>|=>)([A-Z!+|^]*)$"); /*tokenyzer*/
    std::string tmp;
    enum eInference inference;

    regex_search(line, lineMatch, test4);

    std::cout << "    ----0st: " << lineMatch[0].str() << std::endl;
    std::cout << "    ----1st: " << lineMatch[1].str() << std::endl;
    std::cout << "    ----2st: " << lineMatch[2].str() << std::endl;
    std::cout << "    ----3st: " << lineMatch[3].str() << std::endl;



    RulesList_.emplace_back(Rule(lineMatch[1].str(), lineMatch[2].str(), lineMatch[3].str()));
//    RulesList_.push_back(lineMatch[1].str(), lineMatch[2].str(), lineMatch[3].str());
}

/*
 * create initial facts
 */
bool ExpertSystem::lineInitFacts(std::string &line)
{
    bool ret = false;
    std::smatch lineMatch;
    std::regex initialFactsRegExp("^=([A-Z]{0,26}$)");

    if (regex_search(line, lineMatch, initialFactsRegExp)) {
    	std::cout << "OK initial: " << lineMatch[1].str() << std::endl; //debug;
    	ret = true;

    	/*create initial facts*/
    	std::string lineTmp = lineMatch[1].str();
    	for(std::string::iterator it = lineTmp.begin(); it != lineTmp.end(); ++it) {
    		/*have only A..Z characters*/
    		FactsMap_.insert(std::make_pair(*it, INITIAL));
    	}
    	/*//debug
		for(Facts::const_iterator it = FactsMap_.begin(); it != FactsMap_.end(); ++it) {
			std::cout << it->first << std::endl;
			std::cout << it->second.getCondition() << std::endl;
		}
		*/
    }

    return ret;
}

bool ExpertSystem::lineQueryFacts(std::string &line)
{
    bool ret = false;
    std::smatch lineMatch;
    std::regex test2("^\\?([A-Z]{0,26}$)");

    if (regex_search(line, lineMatch, test2)) {
    	std::cout << "OK Query: " << lineMatch[1].str() << std::endl; //debug;
    	ret = true;

    	/*create query list*/
    	std::string lineTmp = lineMatch[1].str();
    	for(std::string::iterator it = lineTmp.begin(); it != lineTmp.end(); ++it) {
    		/*have only A..Z characters*/
    		QueriesList_.emplace_back(*it);
    	}

    	/*//debug
		for(Queries::const_iterator it = QueriesList_.begin(); it != QueriesList_.end(); ++it) {
			std::cout << *it << std::endl;
		}
    	 */
    }

	return ret;
}

bool ExpertSystem::lineValid(std::string &line)
{
	bool ret = true;
    std::smatch lineMatch;

//    std::regex emptyLineRegexp("^\\s*$");
//    std::regex test("^(!?[A-Z])(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$");
//    std::regex test("^(!?[A-Z]\\+|\\||\\^!?[A-Z]*)(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$");

//v1
    std::regex test1("^(!?[A-Z])(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$"); //    Для тех где слева одна буква
    std::regex test2("^(!?[A-Z](\\+!?[A-Z])+)(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$"); // Для плюсов
    std::regex test3("^(!?[A-Z](\\+|\\||\\^)!?[A-Z])(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$"); // Для других операций

    if        (regex_search(line, lineMatch, test1)) {
//        std::cout << "OK1: " << line << std::endl; //debug
    	goto done;
    } else if (regex_search(line, lineMatch, test2)) {
//        std::cout << "OK2: " << line << std::endl; //debug
    	goto done;
    } else if (regex_search(line, lineMatch, test3)) {
//        std::cout << "OK3: " << line << std::endl; //debug
    	goto done;
    } else {
//        std::cout << "KO: " << line << std::endl; //debug
//        throw ESException(INVAL_TOKEN, line); /*TODO: uncoment*/
        goto err; /*TODO: remove hack*/
    }

//    std::cout << "    0st: " << lineMatch[0].str() << std::endl;
//    std::cout << "    1st: " << lineMatch[1].str() << std::endl;
//    std::cout << "    2st: " << lineMatch[2].str() << std::endl;
//    std::cout << "    3st: " << lineMatch[3].str() << std::endl;
//    std::cout << "    4st: " << lineMatch[4].str() << std::endl;
//    std::cout << "    5st: " << lineMatch[5].str() << std::endl;

err:
	ret = false;
done:
    return ret;
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
