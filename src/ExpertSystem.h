#ifndef EXPERT_SYSTEM_H
#define EXPERT_SYSTEM_H

class ExpertSystem {
public:
        static ExpertSystem& Instance();

        void readInput(int ar, char **av);
        bool is_regular_file(const char *fileName);
        void init(int ar, char **av);

        void usage();
private:
        bool verbose_;


        ExpertSystem();
        ~ExpertSystem();

        ExpertSystem(ExpertSystem const &)            = delete;
        ExpertSystem& operator=(ExpertSystem const &) = delete;
};

#endif /*EXPERT_SYSTEM_H*/
