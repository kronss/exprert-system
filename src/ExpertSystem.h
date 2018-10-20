#ifndef EXPERT_SYSTEM_H
#define EXPERT_SYSTEM_H

#include <string>

#include "Fact.h"
//#include "Rule.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


class ExpertSystem {
public:
        static ExpertSystem& Instance();

        void printUsage(const char *);
        void init(int ar, char **av);

        void readInput(int ar, char **av);
        void readFromFile();
        void prepareEngine();
        void resolve();



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


        ExpertSystem();
        ~ExpertSystem();

        ExpertSystem(ExpertSystem const &)            = delete;
        ExpertSystem& operator=(ExpertSystem const &) = delete;
};

#endif /*EXPERT_SYSTEM_H*/
