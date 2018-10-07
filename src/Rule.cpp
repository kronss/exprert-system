
#include "Rule.h"

#include "ESException.h"

#include <cctype> /*isupper*/

/******************************************************************************/
/* PUBLIC                                                                     */
/******************************************************************************/





Rule::Rule(std::string left, std::string inference, std::string right)
: left_(left)
, inference_(initInference(inference))
, right_(right)
//, adjacency_(createAdjency(fullString))
{
	createAdjacency();

}

Rule::Rule(Rule const & rhs)
: left_(rhs.left_),
  inference_(rhs.inference_),
  right_(rhs.right_),
  adjacency_(rhs.adjacency_)
{}

Rule::~Rule(void)
{}

Rule & Rule::operator=(Rule const & rvl)
{
	if (this != &rvl)
	{
		*this = rvl;
	}
	return *this;
}


/******************************************************************************/
/* GETTER                                                                     */
/******************************************************************************/

std::string const & Rule::getLeft() const
{
	return left_;
}

eInference const & Rule::getInference() const
{
	return inference_;
}


std::string const & Rule::getRight() const
{
	return right_;
}

Adjacency const & Rule::getAdjacency() const
{
	return adjacency_;
}



//etc
bool operator==(Rule const lhs, Rule const rhs) {
	if (lhs.getLeft() != rhs.getLeft())
		return false;
	if (lhs.getRight() != rhs.getRight())
		return false;
	return true ;
}

/******************************************************************************/
/* PRIVATE                                                                    */
/******************************************************************************/

//std::string const Rule::toString(void) const {
//	std::ostringstream out;
//
//	out << "If: " << getLeft();
//	out << " - Then: " << getRight() << std::endl;
//	return out.str();
//}

//Facts 				Rule::solve(Facts facts) {
//	std::cout << *this << std::endl;
//	return facts;
//}


void Rule::createAdjacency()
{
	/*before inference character*/
	for (const char & c: left_) {
		if (isupper(c))
			adjacency_.insert(std::make_pair(c, LEFT_SIDE));
	}

	/*after inference character*/
	for (const char & c: right_) {
		if (isupper(c))
			adjacency_.insert(std::make_pair(c, RIGHT_SIDE));
	}
}







eInference Rule::initInference(std::string & inference)
{
	eInference ret;

    if (inference == "=>") {
    	inference = THEN;
    } else if (inference == "<=>") {
    	inference = IF_AND_ONLY_IF;
//        throw ESException(NOT_SUPPORTED); //TODO: rework to sting
    } else {
        throw ESException(NOT_SUPPORTED); //TODO: rework to sting
    }

    return ret;
}


//std::ostream & operator<<(std::ostream & out, Rule const & rhs) {
//	out << rhs.toString();
//	return out;
//}
