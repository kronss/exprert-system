#include "ExpertSystem.h"

#define DEBUG 0

int main(const int argc, char **argv)
{
    try {

        ExpertSystem
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Uncaught exception" << std::endl;
    }

//    system("leaks --queit avm");

    return 0;
}
