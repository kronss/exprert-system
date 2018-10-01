#ifndef FACT_H
#define FACT_H

#include <string>

enum initialFact {
	DEFAULT = 0,
	INITIAL,
};

enum factStatus {
	FALSE_FACT = 0,
	TRUE_FACT = 1
};


class Fact {
public:

	Fact(enum initialFact init = DEFAULT);
//	Fact();
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

#endif /*FACT_H*/
