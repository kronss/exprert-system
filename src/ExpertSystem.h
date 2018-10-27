#ifndef EXPERT_SYSTEM_H
#define EXPERT_SYSTEM_H

#include <string>

#include "cuteColors.h"
#include "Fact.h"

enum SystemStage {
	eINIT               = 0,
	eRULES_TIME         = 1,
	eTRUE_FACTS_TIME    = 2,
	eQUERY_FACTS_TIME   = 3,
	eEXECUTE            = 4,
};

class ExpertSystem {
public:
        static ExpertSystem& Instance();

        void printUsage(const char *);
        void init(int ar, char **av);

        void readInput(int ar, char **av);
        void readFromFile();
        void prepareEngine();
        void resolve();
        void printResults();



        void solve();
        void solveFact(Fact const & fact);


        void BC(); /*UNUSED*/

        void usage();

private:
        bool verbose_;
        std::string fileName_;

        allFacts allFacts_;
//        allFactsRaw allFactsRaw_;

//        Initial initial_;
        Queries queries_;
        Rules rules_;

        SystemStage stage_;



        bool RegularFile(const char *fileName);

        /*work with input*/
        void removeUnusedCharacters(std::string & line);
        bool lineInitFacts(std::string &line);
        bool lineQueryFacts(std::string &line);
        bool lineValid(std::string &line);
        void createRule(std::string &line);

        /*work with matrix*/
        void printMatrix();


        void resolveFact(char q);


        void setSystemStage(enum SystemStage);



        ExpertSystem();
        ~ExpertSystem();

        ExpertSystem(ExpertSystem const &)            = delete;
        ExpertSystem& operator=(ExpertSystem const &) = delete;
};

#endif /*EXPERT_SYSTEM_H*/
