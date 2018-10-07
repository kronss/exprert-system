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


    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Uncaught exception" << std::endl;
    }

//    system("leaks --queit avm");

//	debug("Die hard!\n");
    return 0;
}
