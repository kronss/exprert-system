#ifndef EXPERT_SYSTEM_H
#define EXPERT_SYSTEM_H


class ExpertSystem {
public:
        static ExpertSystem& Instance();




private:
        ExpertSystem();
        ~ExpertSystem();

        ExpertSystem(ExpertSystem const &)            = delete;
        ExpertSystem& operator=(ExpertSystem const &) = delete;
};












#endif /*EXPERT_SYSTEM_H*/
