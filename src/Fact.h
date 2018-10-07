#ifndef FACT_H
#define FACT_H

#include <string>
#include <map>
#include <list>
#include "Rule.h"

class Fact;

enum initialFactStatus {
	INITIAL = 0,  /*true always! Does not reassign*/
	DEFAULT,      /*false*/
};

enum eFactValue {
	eTRUE = 0,
	eFALSE,
	eUNKNOWN,
};

typedef std::map<const char, Fact> Facts;    /*initial true facts*/
typedef std::list<const char> Queries;

class Fact {
public:
	Fact(enum initialFactStatus init = DEFAULT);
    ~Fact();

    Fact(Fact const &);
    Fact& operator=(Fact const &);

    bool getIsInitial() const;
    bool getCondition() const;

    void setCondition(enum eFactValue newStatus);

private:
    const bool initial_;
    bool       condition_;
};

/*TODO
std::ostream 			& operator<<(std::ostream & out, Fact const & rhs);
*/

#endif /*FACT_H*/
