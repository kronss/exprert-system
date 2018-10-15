
#include "Rule.h"

#include "ESException.h"

#include <iostream>
#include <cctype> /*isupper*/

#define ES
#include "OPN.cpp"
#undef ES
/******************************************************************************/
/* PUBLIC                                                                     */
/******************************************************************************/



//friend

Rule::Rule(std::string left, std::string inference, std::string right)
: left_(left)
, inference_(initInference(inference))
, right_(right)
, leftPostfix_(InfixToPostfix(left))
//, adjacency_(createAdjency(fullString))
{
	validateLeft();
//	validateInference();       //TODO!!!!!!!!!!
//	validateRight();

	createAdjacency();

	createExpression();


	std::cout << "infix:   " << left_ << std::endl;
	std::cout << "postfix: " << leftPostfix_ << std::endl;

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

Expression const & Rule::getExpressionLeft() const
{
	return expressionLeft_;
}

Expression const & Rule::getExpressionRight() const
{
	return expressionRight_;
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

#include <unistd.h>
void Rule::validateLeft()
{
	std::string &str = left_;

	if (str.empty())
		throw ESException("empty left part in rule ");


	//1st
	//2nd
	//3rd

}



void validateRight()
{

}








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

void Rule::createExpression()
{
	/*before inference character*/
	for (const char & c: left_) {
		if (isupper(c))
			expressionLeft_.emplace_back(c); //  (std::make_pair(c, LEFT_SIDE));
		else
			expressionLeft_.emplace_back(c); //  (std::make_pair(c, LEFT_SIDE));
	}

	/*after inference character*/
	for (const char & c: right_) {
		if (isupper(c))
			expressionRight_.emplace_back(c); //  (std::make_pair(c, LEFT_SIDE));
		else
			expressionRight_.emplace_back(c); //  (std::make_pair(c, LEFT_SIDE));
	}
}

eInference Rule::initInference(std::string & inference)
{
	eInference ret;

    if (inference == "=>") {
    	inference = THEN;
    } else if (inference == "<=>") {
    	inference = IF_AND_ONLY_IF;
        throw ESException("Not supported inference `<=>`");
    } else {
        throw ESException("Not supported inference");
    }

    return ret;
}


//std::ostream & operator<<(std::ostream & out, Rule const & rhs) {
//	out << rhs.toString();
//	return out;
//}
