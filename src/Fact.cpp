#include "Fact.h"

#include "ESException.h"
#include "debug.h"

#define debug 0

/******************************************************************************/
/* PUBLIC                                                                     */
/******************************************************************************/
Fact::Fact(char value, enum eFactValue condition, enum initialFactStatus init)
: letter_(value)
, initial_(init)
, condition_(condition)
{}

Fact::~Fact()
{}

Fact::Fact(Fact const &rval)
:
initial_(rval.initial_),
condition_(rval.condition_),
letter_(rval.letter_)
{}

Fact& Fact::operator = (Fact const &rval)
{
	if (this != &rval)
	{
	    *this = rval;
	}
	return *this;
}

char Fact::getLetter() const
{
	return letter_;
}

enum eFactValue Fact::getCondition() const
{
	return condition_;
}

const bool Fact::getIsInitial() const
{
	return initial_;
}

/*SETTER*/
void Fact::setIsInitial(enum initialFactStatus isInit)
{
	initial_ = isInit;
}

void Fact::setCondition(enum eFactValue newStatus)
{
	if (eUNKNOWN == newStatus && eINITIAL == initial_) return;

	condition_ = newStatus;
}

void Fact::addDependsOnRule(Rule & rule)
{
	dependeOnRules_.emplace_back(rule);
//	dependeOnRules_.emplace_back(rule);
}

std::vector<Rule> & Fact::getDependsOnRule()
{
	return dependeOnRules_;
//	dependeOnRules_.emplace_back(rule);
}


bool Fact::operator == ( const char& rhs ) const
{
    return getLetter() == rhs;
}


/******************************************************************************/
/* PRIVATE                                                                    */
/******************************************************************************/







//std::ostream &operator << (std::ostream & o, const Victim &rhs)


std::ostream & operator << (std::ostream & o, Fact const & rhs) {
	o << rhs.getLetter() << " == " <<  (rhs.getCondition() == eTRUE ? "true" : rhs.getCondition() == eFALSE ? "false" : "unknown"); // << " = " << static_cast<int>(rhs.getCondition());
	return o;
}

