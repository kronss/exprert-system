#include "Rule.h"
#include "ESException.h"

#include <iostream>
#include <cctype> /*isupper*/

#define ES
#include "InfixToPostfix.cpp"
//#undef ES


/******************************************************************************/
/* PUBLIC                                                                     */
/******************************************************************************/

Rule::Rule(std::string left, std::string inference, std::string right)
: left_(left)
, inference_(initInference(inference))
, right_(right)
, leftPostfix_(InfixToPostfix(left))
, rightPostfix_(InfixToPostfix(right))

//, adjacency_(createAdjency(fullString))
{
	validateExpresion(left_);
	validateExpresion(right_);

//	HACK_checkOperatorsRight(right_);

	createAdjacency();
	createExpression(); /*UNUSED?*/

//	std::cout << "infix:   " << left_ << std::endl; //debug
//	std::cout << "postfix: " << leftPostfix_ << std::endl; //debug
}

Rule::Rule(Rule const & rhs)
: left_(rhs.left_)
, inference_(rhs.inference_)
, right_(rhs.right_)
, adjacency_(rhs.adjacency_)
, leftPostfix_(rhs.leftPostfix_)
, rightPostfix_(rhs.leftPostfix_)
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

/*will work with copy*/
std::string const & Rule::getleftPostfix_() const
{
	return leftPostfix_;
}

/*will work with copy*/
std::string Rule::getRightPostfix_() const
{
	return rightPostfix_;
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

void Rule::validateExpresion(std::string &str)
{
	int alpha = 0;
	int oper = 1; /*fix cases "+B"*/
	int oposite = 0;

	if (str.empty())
		throw ESException("empty left part in rule ");

	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {

		if (*it == '(' || *it == ')') continue ; /*handle it in OPN.cpp*/

		else if (isalnum(*it)) {
			if (++alpha > 1) throw ESException("invalid rules expresion: too much parametrs");
			oper = 0;
//			oposite = 0;
		}

		else if (*it == '+' || *it == '|' || *it == '^') {
			if (++oper > 1) throw ESException("invalid rules expresion: too much operators");
			alpha = 0;
			oposite = 0;
		}

		else if (*it == '!') {
			if (++oposite > 1) throw ESException("invalid rules expresion: to much oposites");
			alpha = 0;
		}

		else {
			throw ESException("invalid rules expresion");
		}
	}

	/* case:
	 *  A+B+
	 *  empty
	 * */
	if (alpha != 1)
		throw ESException("invalid rules expresion");

	return ;
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

void Rule::createExpression() /*UNUSED?*/
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
