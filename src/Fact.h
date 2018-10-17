#ifndef FACT_H
#define FACT_H

#include <string>
#include <map>
#include <vector>
#include <list>
#include "Rule.h"
#include <iostream>


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
typedef std::vector<class Fact>    allFacts;
typedef std::vector<int> allFactsRaw;
//typedef std::map<const char, Fact> allFacts;    /*initial true facts*/
typedef std::list<int> Initial;
typedef std::list<int> Queries;

class Fact {
public:
	Fact(char value, enum eFactValue condition, enum initialFactStatus init = eDEFAULT);
    ~Fact();

    Fact(Fact const &);
    Fact& operator=(Fact const &);

    char             getValue() const;
    enum eFactValue  getCondition() const;
    const bool       getIsInitial() const;

    bool operator == ( const char& rhs ) const;

    void setIsInitial(enum initialFactStatus isInit);
    void setCondition(enum eFactValue newStatus);

private:
    char            value_;
    enum eFactValue condition_;
    bool            initial_;
};


std::ostream & operator << (std::ostream & o, Fact const & rhs);


#endif /*FACT_H*/
