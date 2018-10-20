#include "ExpertSystem.h"
#include "ESException.h"
#include "debug.h"
#include <iostream>

#define DEBUG 1

int main(const int argc, char **argv)
{
//	debug("Hello world!\n");
    try {
    	ExpertSystem& expertSystem = ExpertSystem::Instance();
    	expertSystem.readInput(argc, argv);
    	expertSystem.readFromFile();
    	expertSystem.prepareEngine();
    	expertSystem.resolve();

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Uncaught exception" << std::endl;
    }

//    system("leaks --queit avm");

//	debug("Die hard!\n");
    return 0;
}

/*
void fillFactsWithRelevantRules {

	Facts facts;
	Rules rules;

	for (auto& fact : facts) {
		for ( auto & rule : rules) {
			if (hasFactOnRight(fact.letter))
		}
	}
}

*/
