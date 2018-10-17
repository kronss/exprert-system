#ifndef EXPERT_SYSTEM_H
#define EXPERT_SYSTEM_H

#include <string>

#include "Fact.h"
//#include "Rule.h"



class ExpertSystem {
public:
        static ExpertSystem& Instance();

        void printUsage(const char *);
        void init(int ar, char **av);

        void readInput(int ar, char **av);
        void readFromFile();
        void prepareEngine();

        void solve();
        void solveFact(Fact const & fact);


        void BC();

        void usage();

private:
        bool verbose_;
        std::string fileName_;

        allFacts allFacts_;
        allFactsRaw allFactsRaw_;

        Initial Initial_;
        Queries QueriesList_;
        Rules Rules_;

        Rules usedRules_;


        bool RegularFile(const char *fileName);

        /*work with input*/
        void removeUnusedCharacters(std::string & line);
        bool lineInitFacts(std::string &line);
        bool lineQueryFacts(std::string &line);
        bool lineValid(std::string &line);
        void createRule(std::string &line);

        /*work with matrix*/
        void printMatrix();





        ExpertSystem();
        ~ExpertSystem();

        ExpertSystem(ExpertSystem const &)            = delete;
        ExpertSystem& operator=(ExpertSystem const &) = delete;
};

#endif /*EXPERT_SYSTEM_H*/
