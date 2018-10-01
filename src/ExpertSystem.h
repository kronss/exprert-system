#ifndef EXPERT_SYSTEM_H
#define EXPERT_SYSTEM_H

#include <string>
#include "Fact.hpp"

#define ALWAYSTRUE true


struct Rule {
    std::string left;
    std::string asign;
    std::string right;
};




class ExpertSystem {
public:
        static ExpertSystem& Instance();

        void printUsage(const char *);
        void init(int ar, char **av);

        void readInput(int ar, char **av);
        void readFromFile();
        void usage();

private:
        bool verbose_;
        std::string fileName_;

        Facts FactsMap_;
        Queries QueriesList_;

        bool RegularFile(const char *fileName);

        /*work with input*/
        void removeUnusedCharacters(std::string & line);
        bool lineInitFacts(std::string &line);
            bool lineQueryFacts(std::string &line);
        bool lineValid(std::string &line);
        void createRule(std::string &line);



        ExpertSystem();
        ~ExpertSystem();

        ExpertSystem(ExpertSystem const &)            = delete;
        ExpertSystem& operator=(ExpertSystem const &) = delete;
};

#endif /*EXPERT_SYSTEM_H*/
