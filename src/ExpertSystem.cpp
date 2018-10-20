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
#include <algorithm>


//#include <boost/regex.hpp>


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
	throw (ESException());
}

void ExpertSystem::readFromFile()
{
    std::fstream fs(fileName_);
    int lineNbr = 0;
    std::string line;


    DBG("File is %s", fileName_.c_str());

    if (!RegularFile(fileName_.c_str())) {
        DBG("Bad file");
        std::string what = "Bad file: ";
        what += fileName_.c_str();
        throw ESException(what);
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

//    std::cout << "------------------------------------" << std::endl;
//    for (auto const& i : Rules_) {
//        std::cout << i.getLeft() << std::endl;
//        std::cout << i.getInference() << std::endl;
//        std::cout << i.getRight() << std::endl;
//        std::cout << "------------------------------------" << std::endl;
//    }
}


void ExpertSystem::prepareEngine()
{
//	std::map<char, int> adjacency;
//	printMatrix();

	for ( char c: initial_ ) {
		allFacts_.at(c).setIsInitial(eINITIAL); /*UNUSED*/
		allFacts_.at(c).setCondition(eTRUE);
	}

	for ( char c: queries_ ) {
//		(allFacts_[c]).setCondition(eUNKNOWN); /*? separate array*/
	}


	//debug
	for (auto & f : allFacts_) {
		std::cout << f.first << std::endl;
		for (auto & r : f.second.dependeOnRules_) {
			std::cout << r.getLeft() << std::endl;
		}
		std::cout << "======================" << std::endl;
}

}

//
//void ExpertSystem::BC()
//{
//	allFacts::const_iterator	fit  = allFacts_.begin();
//	allFacts::const_iterator	fite = allFacts_.end();
//
//	QueriesList_.begin();
//
//	for (; fit != fite; fit++) {
//		solveFact(*fit);
////		clearUsedRules();
//	}
//
//	return ;
//
//
//
//
//}
//
//
//
//
//
//
//
//
//
//
//void ExpertSystem::solve() {
//
//	allFacts::const_iterator	fit  = allFacts_.begin();
//	allFacts::const_iterator	fite = allFacts_.end();
//
//	for (; fit != fite; fit++) {
//		solveFact(*fit);
//		clearUsedRules();
//	}
//
//	return ;
//}
//
//
//void ExpertSystem::solveFact(Fact const & fact) {
//
//	Rules::const_iterator	rit  = Rules_.begin();
//	Rules::const_iterator	rite = Rules_.end();
//
//	for (; rit != rite; rit++) {
//
//		std::string		rhs = rit->getRight();
//
//		if (rhs.find(fact.getValue()) != std::string::npos) {
//
//			if (! ruleUsed(*rit)) {
//
//				addUsedRules(*rit);
//				solveRule(*rit, fact);
//			}
//		}
//	}
//}
//
//bool					ExpertSystem::ruleUsed(Rule const & rule) {
//	Rules::const_iterator	rit  = getUsedRules().begin();
//	Rules::const_iterator	rite = getUsedRules().end();
//
//	for (; rit != rite; rit++) {
//		if (rule == *rit)
//			return true;
//	}
//
//	return false;
//}


void ExpertSystem::printMatrix() {
    for (Rule & r: rules_) {
        for (auto & p : r.getAdjacency()) {
            std::cout << p.first << " | " ;
        }

        std::cout << std::endl;

        for (auto & p : r.getAdjacency()) {
			std::cout << p.second << " | " ;
		}

        std::cout << std::endl;
    }
}



void ExpertSystem::resolveFact(char q)
{

}






void ExpertSystem::resolve()
{
	for (char q : queries_) {
		resolveFact(q);
	}
}







//void ExpertSystem::printMatrix() {
//    for (Rule& r: Rules_) {
//        for (auto& p : r.getAdjacency()) {
//            std::cout << p.first << p.second << std::endl;
//        }
//    }
//}


/******************************************************************************/
/* PRIVATE                                                                    */
/******************************************************************************/


//void ExpertSystem::createHuckN1()
//{
//
//}


// A => B + C + D


void ExpertSystem::createRule(std::string &line)
{
    std::smatch lineMatch;
                     /*(   1st    )( 2nd  )(   3rd    )*/
    std::regex tokens("^([\\(\\)A-Z!+|^]*)(<=>|=>)([A-Z!+|^]*)$"); /*tokenyzer*/
    std::string tmp;
    enum eInference inference;

    regex_search(line, lineMatch, tokens);

//    std::cout << "    ----0st: " << lineMatch[FULL_STRING].str() << std::endl;
//    std::cout << "    ----1st: " << lineMatch[LEFT_PART].str()   << std::endl;
//    std::cout << "    ----2st: " << lineMatch[INFERENCE].str()   << std::endl;
//    std::cout << "    ----3st: " << lineMatch[RIGHT_PART].str()  << std::endl;

    Rule r(lineMatch[LEFT_PART].str(),
			 lineMatch[INFERENCE].str(),
			 lineMatch[RIGHT_PART].str());

    rules_.emplace_back(r);

	for (char c: line) {
		if (isupper(c)) {
//			Fact a(c, eUNKNOWN);
			allFacts_.emplace(c, Fact(c, eUNKNOWN)); // @suppress("Method cannot be resolved")
		}
			//allFacts_.emplace(c, Fact(c, eFALSE)); //  (std::make_pair(c, LEFT_SIDE));
	}

	for (char c: r.getRight()) {
		if (isupper(c)) {
			allFacts_.at(c).addDependsOnRule(r);
		}
	}
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
    		initial_.emplace_back(*it);

    		allFacts_.at(*it).setCondition(eTRUE);
    		allFacts_.at(*it).setCondition(eTRUE);
//    		allFacts_[*it].setIsInitial(eINITIAL);
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
    		queries_.emplace_back(*it);

//    		allFacts_.emplace_back(*it);
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
	bool ret = false;
//    std::smatch lineMatch;

//    std::regex emptyLineRegexp("^\\s*$");
    std::regex usedCharacters("^[A-Z<=>+!?()|^]*$");
//    std::regex test("^(!?[A-Z]\\+|\\||\\^!?[A-Z]*)(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$");

    if (regex_match(line, usedCharacters)) {
    	std::cout << "line valid : " << line << std::endl;
    	ret = true;
    }

    return ret;
//v1
//    std::regex test1("^(!?[A-Z])(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$"); //    Для тех где слева одна буква
//    std::regex test2("^(!?[A-Z](\\+!?[A-Z])+)(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$"); // Для плюсов
//    std::regex test3("^(!?[A-Z](\\+|\\||\\^)!?[A-Z])(=>|<=>)(!?[A-Z](\\+!?[A-Z])*)$"); // Для других операций
//
//    if        (regex_search(line, lineMatch, test1)) {
////        std::cout << "OK1: " << line << std::endl; //debug
//    	goto done;
//    } else if (regex_search(line, lineMatch, test2)) {
////        std::cout << "OK2: " << line << std::endl; //debug
//    	goto done;
//    } else if (regex_search(line, lineMatch, test3)) {
////        std::cout << "OK3: " << line << std::endl; //debug
//    	goto done;
//    } else {
////        std::cout << "KO: " << line << std::endl; //debug
////        throw ESException(INVAL_TOKEN, line); /*TODO: uncoment*/
//        goto err; /*TODO: remove hack*/
//    }

//    std::cout << "    0st: " << lineMatch[0].str() << std::endl;
//    std::cout << "    1st: " << lineMatch[1].str() << std::endl;
//    std::cout << "    2st: " << lineMatch[2].str() << std::endl;
//    std::cout << "    3st: " << lineMatch[3].str() << std::endl;
//    std::cout << "    4st: " << lineMatch[4].str() << std::endl;
//    std::cout << "    5st: " << lineMatch[5].str() << std::endl;

//err:
//	ret = false;
//done:
//    return ret;
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
