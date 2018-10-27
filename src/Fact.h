#ifndef FACT_H
#define FACT_H

#include <string>
#include <map>
#include <vector>
#include <list>
#include "Rule.h"
#include <iostream>

#include "cuteColors.h"


enum initialFactStatus {
	eDEFAULT = 0,      /*false*/
	eINITIAL = 1,  /*true always! Does not reassign*/
};

enum eFactValue {
	eTRUE = 0,
	eFALSE,
	eUNKNOWN,
};

class Fact;
typedef std::map<char, Fact>    allFacts;
typedef std::vector<char> Initial;
typedef std::vector<char> Queries;

class Fact {
public:
    Fact(char letter, enum eFactValue condition, enum initialFactStatus init = eDEFAULT);
    ~Fact();

    Fact(Fact const &);
    Fact& operator=(Fact const &);

    char             getLetter() const;
    enum eFactValue  getCondition() const;
    bool       getIsInitial() const;

    bool operator == ( const char& rhs ) const;

    void setIsInitial(enum initialFactStatus isInit);
    void setCondition(enum eFactValue newStatus);

    void addDependsOnRule(Rule & rule);
    std::vector<Rule> & getDependsOnRule();

private:
    char              letter_;
    eFactValue        condition_;
    bool              initial_; /*UNUSED*/

    std::vector<Rule> dependeOnRules_;
};

std::ostream & operator << (std::ostream & o, Fact const & rhs);

#endif /*FACT_H*/
