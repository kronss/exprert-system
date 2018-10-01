
#include "Rule.hpp"
#include "ESException.h"

/******************************************************************************/
/* PUBLIC                                                                     */
/******************************************************************************/


eInference initInference(std::string & inference)
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


Rule::Rule(std::string left, std::string inference, std::string right)
: left_(left),
  inference_(initInference(inference)),
  right_(right)
{
    /*check rules*/



}

Rule::Rule(Rule const & rvl)
: left_(rvl.left_),
  inference_(rvl.inference_),
  right_(rvl.right_)
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





//etc
bool operator==(Rule const lhs, Rule const rhs) {
	if (lhs.getLeft() != rhs.getLeft())
		return false;
	if (lhs.getRight() != rhs.getRight())
		return false;
	return true ;
}

//std::ostream & operator<<(std::ostream & out, Rule const & rhs) {
//	out << rhs.toString();
//	return out;
//}
