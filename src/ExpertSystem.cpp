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
	std::cout << "Fact1 " << q << ":" << f << std::endl; //debug
	if (f.getCondition() == eTRUE) {
		return;
	}
	if (f.getCondition() == eFALSE) {
		return;
	}

	if (f.getDependsOnRule().empty()) {
		/*no depends rule for this fact => false*/
		std::cout << "----------------------------------Fact " RED << f.getLetter() << RESET " set by " RED "false" RESET << std::endl;
		f.setCondition(eFALSE);
		return;
	}

//	DBG();
//
//	if   (f.dependeOnRules_.empty()) std::cout << "empty" << std::endl;
//	else                             std::cout << "not empty" << std::endl;

	std::cout << "Fact2 " << q << ":" << f << std::endl; //debug
//	for (auto & r : f.dependeOnRules_) {
//			std::cout << "dependeOn : " << r.getLeft() << std::endl;
//		}
//	std::cout << "+++++++++++++++" << std::endl;

	for ( Rule & r : f.getDependsOnRule() ) {
//		DBG();

		/*let check all facts in depends on part of rule*/
		for (const char & c : r.getLeft()) {
			if (isupper(c) && allFacts_.at(c).getCondition() == eUNKNOWN) {
				ExpertSystem::resolveFact(c);
			}
		}

		std::cout << "dependeOn1 : " << r.getLeft() << std::endl;
		std::cout << "dependeOn2 : " << r.getleftPostfix_() << std::endl;

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
					std::cout << "Fact: postfix " << postfix << ":" << c << std::endl; //debug
					throw ESException("Unknown fact in postfix");
				}
			}
		}


		if (EvaluatePostfix(postfix)) {
			f.setCondition(eTRUE);
		} else {
			f.setCondition(eFALSE);
		}


		std::cout << "Fact5 " << q << ":" << f << std::endl; //debug
		std::cout << "Postfix string: "<< postfix << std::endl;
		for ( char c : postfix) {
			std::cout << c ;
		}
		std::cout << std::endl;
	}
}






void ExpertSystem::resolve()
{
	std::cout << "----- Resolve fact -----" << std::endl;
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
			allFacts_.emplace(c, Fact(c, eUNKNOWN)); // @suppress("Method cannot be resolved")
		}
	}

	for (char c: r.getRight()) {
		if (isupper(c)) {
//			std::cout << __LINE__ << ":" << " r.getRight() === " << r.getRight() << std::endl;
//			std::cout << __LINE__ << ":" << " r.getLeft()  === " << r.getLeft()  << std::endl;
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
//    		initial_.emplace_back(*it);

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
    	std::cout << "OK Query: " << lineMatch[1].str() << std::endl; //debug;
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
