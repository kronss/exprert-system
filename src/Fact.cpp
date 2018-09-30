#include "Fact.hpp"
#include "ESException.h"
#include "debug.h"

#define debug 0

/******************************************************************************/
/* PUBLIC                                                                     */
/******************************************************************************/
Fact::Fact(enum initialFact init)
:
initial_(init),
condition_(init == INITIAL ? TRUE_FACT : FALSE_FACT)
{}

Fact::~Fact()
{}

Fact::Fact(Fact const &rval)
:
initial_(rval.initial_),
condition_(rval.condition_)
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

void Fact::setCondition(enum factStatus newStatus)
{
	if (initial_ && newStatus == FALSE_FACT) {
		/*trying reassign initial fact, ignored*/
		return;
//		throw (ESException(REASSIGN_INIT));
	}
	condition_ = newStatus;
}

/******************************************************************************/
/* PRIVATE                                                                    */
/******************************************************************************/

