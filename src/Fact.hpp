#ifndef FACT_H
#define FACT_H

#include "Rule.hpp"

#include <string>
#include <map>
#include <list>

class Fact;

enum initialFact {
	DEFAULT = 0, /*false*/
	INITIAL,     /*true always! Does not reassign*/
};

enum factStatus {
	FALSE_FACT = 0,
	TRUE_FACT = 1,
};

typedef std::map<const char, Fact> Facts;		/*initial true facts*/
typedef std::list<const char> Queries;

class Fact {
public:
	Fact(enum initialFact init = DEFAULT);
    ~Fact();

    Fact(Fact const &);
    Fact& operator=(Fact const &);

    bool getIsInitial() const;
    bool getCondition() const;

    void setCondition(enum factStatus newStatus);

private:
    const bool initial_;
    bool       condition_;
};

/*TODO
std::ostream 			& operator<<(std::ostream & out, Fact const & rhs);
*/

#endif /*FACT_H*/
