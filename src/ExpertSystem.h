#ifndef EXPERT_SYSTEM_H
#define EXPERT_SYSTEM_H

#include <string>

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

        bool RegularFile(const char *fileName);
        void removeUnusedCharacters(std::string & line);
        bool lineValid(std::string &line);


        ExpertSystem();
        ~ExpertSystem();

        ExpertSystem(ExpertSystem const &)            = delete;
        ExpertSystem& operator=(ExpertSystem const &) = delete;
};

#endif /*EXPERT_SYSTEM_H*/
