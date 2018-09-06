#ifndef EXPERT_SYSTEM_H
#define EXPERT_SYSTEM_H

#include <string>

class ExpertSystem {
public:
        static ExpertSystem& Instance();

        void readInput(int ar, char **av);
        void printUsage(const char *);
        bool isRegularFile(const char *fileName);
        void init(int ar, char **av);

        void usage();
private:
        bool verbose_;
        std::string fileName_;


        ExpertSystem();
        ~ExpertSystem();

        ExpertSystem(ExpertSystem const &)            = delete;
        ExpertSystem& operator=(ExpertSystem const &) = delete;
};

#endif /*EXPERT_SYSTEM_H*/
