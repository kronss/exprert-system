#include "ExpertSystem.h"
#include "ESException.h"
#include "debug.h"
#include <iostream>
#include "cuteСolors.h"

#define DEBUG 0

int main(const int argc, char **argv)
{
//	DBG("Hello world!\n");
    try {
    	ExpertSystem& expertSystem = ExpertSystem::Instance();
    	expertSystem.readInput(argc, argv);
    	expertSystem.readFromFile();
    	expertSystem.prepareEngine();
    	expertSystem.resolve();

    } catch (std::exception &e) {
        std::cerr << RED << "\tERROR:\t" RESET << e.what() << std::endl ;
    } catch (...) {
        std::cerr << RED << "\tERROR:\t" RESET << "Uncaught exception" << std::endl;
    }

//    system("leaks --queit avm");

//    DBG("Die hard!\n");
    return 0;
}
