#include "Fact.h"

#include "ESException.h"
#include "debug.h"

#define debug 0

/******************************************************************************/
/* PUBLIC                                                                     */
/******************************************************************************/
Fact::Fact(char value, enum eFactValue condition, enum initialFactStatus init)
: value_(value)
, initial_(init)
, condition_(condition)
{}

Fact::~Fact()
{}

Fact::Fact(Fact const &rval)
:
initial_(rval.initial_),
condition_(rval.condition_),
value_(rval.value_)
{}

Fact& Fact::operator = (Fact const &rval)
{
	if (this != &rval)
	{
	    *this = rval;
	}
	return *this;
}

char Fact::getValue() const
{
	return value_;
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

bool Fact::operator == ( const char& rhs ) const
{
    return getValue() == rhs;
}


/******************************************************************************/
/* PRIVATE                                                                    */
/******************************************************************************/







//std::ostream &operator << (std::ostream & o, const Victim &rhs)


std::ostream & operator << (std::ostream & o, Fact const & rhs) {
	o << static_cast<char>(rhs.getValue() + 'A') << " == " <<  (rhs.getCondition() == eTRUE ? "true" : rhs.getCondition() == eFALSE ? "false" : "unknown"); // << " = " << static_cast<int>(rhs.getCondition());
	return o;
}

