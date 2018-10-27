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


#define ES
#include "PostfixEvaluation.cpp"
//#include <boost/regex.hpp>


#define DEBUG 0

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

//        std::cout << lineNbr << ". " << line << std::endl; //debug
        if (line.empty()) {
            continue ;
        } else if (lineInitFacts(line)) {
        	setSystemStage(eTRUE_FACTS_TIME);
        } else if (lineQueryFacts(line)) {
        	setSystemStage(eQUERY_FACTS_TIME);
        } else if (lineValid(line)) {
        	setSystemStage(eRULES_TIME);
        	createRule(line);
        } else {
        	throw ESException("Bad input");
//        	continue;
        }
    }
	setSystemStage(eEXECUTE);

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

//	for ( char c: initial_ ) {
//		allFacts_.at(c).setIsInitial(eINITIAL); /*UNUSED*/
//		allFacts_.at(c).setCondition(eTRUE);
//	}

//	for ( char c: queries_ ) {
////		(allFacts_[c]).setCondition(eUNKNOWN); /*? separate array*/
//	}


/*	//debug
	for (auto & f : allFacts_) {
		std::cout << f.first << std::endl;
		for (auto & r : f.second.dependeOnRules_) {
			std::cout << r.getLeft() << std::endl;
		}
		std::cout << "======================" << std::endl;
	}
*/

//	for (auto & r : rules_) {
//		std::cout << r.getleftPostfix_() << std::endl;
//		std::cout << "======================" << std::endl;
//	}
}

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
	Fact & f = allFacts_.at(q);
//	std::cout << "Fact1 " << q << ":" << f << std::endl; //debug
	if (f.getCondition() == eTRUE) {
		return;
	}
	if (f.getCondition() == eFALSE) {
		return;
	}

	if (f.getDependsOnRule().empty()) {
		/*no depends rule for this fact => false*/
//		std::cout << "----------------------------------Fact " RED << f.getLetter() << RESET " set by " RED "false" RESET << std::endl; //debug
		f.setCondition(eFALSE);
		return;
	}

	for ( Rule & r : f.getDependsOnRule() ) {

		/*let check all facts in depends on part of rule*/
		for (const char & c : r.getLeft()) {
			if (isupper(c) && allFacts_.at(c).getCondition() == eUNKNOWN) {
				ExpertSystem::resolveFact(c);
			}
		}

		/*in this part all fact needed for resolve this fact is known*/
		std::string postfix = r.getleftPostfix_();

		/*change Facts to values*/
		for (char & c : postfix) {
			if (isupper(c)) {
				if ( allFacts_.at(c).getCondition() == eTRUE ) {
					c = '1';
				} else if ( allFacts_.at(c).getCondition() == eFALSE ) {
					c = '0';
				} else {
//					std::cout << "Fact: postfix " << postfix << ":" << c << std::endl; //debug
					throw ESException("Unknown fact in postfix");
				}
			}
		}

		if (EvaluatePostfix(postfix)) {
			f.setCondition(eTRUE);
			break;
		} else {
			f.setCondition(eFALSE);
		}

//		std::cout << "Fact5 " << q << ":" << f << std::endl; //debug
//		std::cout << "Postfix string: "<< postfix << std::endl;
	}
}

void ExpertSystem::resolve()
{
//	std::cout << "----- Resolve fact -----" << std::endl; //debug
	for (char q : queries_) {
		resolveFact(q);
	}
}

void ExpertSystem::printResults()
{
	for (char c : queries_) {
		eFactValue condition = allFacts_.at(c).getCondition();

		std::cout << "Fact " << CYAN << c << RESET << " is ";
		if (eTRUE == condition) {
			std::cout << GREEN << "true";
		} else if (eFALSE == condition) {
			std::cout << RED << "false";
		} else if (eUNKNOWN == condition) {
			std::cout << YELLOW << "unknown";
		} else {
			throw ESException("Unknown fact condition");
		}
		std::cout << RESET << std::endl;
	}
}


/******************************************************************************/
/* PRIVATE                                                                    */
/******************************************************************************/

void ExpertSystem::createRule(std::string &line)
{
                         /*(-------1st------)(--2nd-)(---3rd----)*/
//    std::regex   tokens("^([\\(\\)A-Z!+|^]*)(<=>|=>)([A-Z!+|^]*)$"); /*tokenyzer*/
    std::regex   tokens("^([\\(\\)A-Z!+|^]*)(<=>|=>)([A-Z+]*)$"); /*tokenyzer*/
    std::smatch  lineMatch;
    std::string  tmp;
    eInference   inference;

    if (regex_search(line, lineMatch, tokens)) {
    	;
    } else {
    	throw ESException("Invalid characters in rule");
    }

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
			allFacts_.emplace(c, Fact(c, eUNKNOWN)); // @suppress("Method cannot be resolved")
		}
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
//    	std::cout << "OK initial: " << lineMatch[1].str() << std::endl; //debug;
    	ret = true;

    	/*create initial facts*/
    	std::string lineTmp = lineMatch[1].str();
    	for(std::string::iterator it = lineTmp.begin(); it != lineTmp.end(); ++it) {
    		/*have only A..Z characters*/
    		//TODO: remove duplication
			allFacts_.emplace(*it, Fact(*it, eTRUE, eINITIAL)); //, eINITIAL)); // @suppress("Method cannot be resolved")
    		allFacts_.at(*it).setCondition(eTRUE);
    		allFacts_.at(*it).setIsInitial(eINITIAL);
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
//    	std::cout << "OK Query: " << lineMatch[1].str() << std::endl; //debug;
    	ret = true;

    	/*create query list*/
    	std::string lineTmp = lineMatch[1].str();
    	for(std::string::iterator it = lineTmp.begin(); it != lineTmp.end(); ++it) {
    		/*have only A..Z characters*/
			allFacts_.emplace(*it, Fact(*it, eUNKNOWN)); // @suppress("Method cannot be resolved")
    		allFacts_.at(*it).setCondition(eUNKNOWN);
    		queries_.emplace_back(*it);
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

    std::regex usedCharacters("^[A-Z<=>+!?()|^]*$");

    if (regex_match(line, usedCharacters)) {
//    	std::cout << "line valid : " << line << std::endl;
    	ret = true;
    }

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

ExpertSystem::ExpertSystem()
: verbose_(false)
, stage_(eINIT)
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

void ExpertSystem::setSystemStage(enum SystemStage stage)
{
	switch (stage) {

	default:
		throw ESException("Not expected stage in Expert System");

	case eINIT:
		throw ESException("Unexpected init stage in Expert System");

	case eRULES_TIME:
		if (!(eRULES_TIME == stage_ || eINIT == stage_))
			throw ESException("Unexpected rule in Expert System");
		break;

	case eTRUE_FACTS_TIME:
		if (eRULES_TIME != stage_)
			throw ESException("Unexpected True facts in Expert System");
		break;

	case eQUERY_FACTS_TIME:
		if (eTRUE_FACTS_TIME != stage_)
			throw ESException("Unexpected query facts in Expert System");
		break;

	case eEXECUTE:
		if (eQUERY_FACTS_TIME != stage_)
			throw ESException("Unexpected execute stage in Expert System");
		break;
	}

	stage_ = stage;
}

void ExpertSystem::usage()
{
	std::cerr << "" << std::endl;
}

