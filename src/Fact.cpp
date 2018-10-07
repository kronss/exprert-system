#include "Fact.h"

#include "ESException.h"
#include "debug.h"

#define debug 0

/******************************************************************************/
/* PUBLIC                                                                     */
/******************************************************************************/
Fact::Fact(char value, enum initialFactStatus init)
:
initial_(init),
condition_(init == INITIAL ? eTRUE : eFALSE),
value_(value)
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

bool Fact::getIsInitial() const
{
	return initial_;
}

bool Fact::getCondition() const
{
	return condition_;
}

void Fact::setCondition(enum eFactValue newStatus)
{
	if (initial_ && newStatus == eTRUE) {
		/*trying reassign initial fact, ignored*/
		return;
//		throw (ESException(REASSIGN_INIT));
	}
	condition_ = newStatus;
}

/******************************************************************************/
/* PRIVATE                                                                    */
/******************************************************************************/

