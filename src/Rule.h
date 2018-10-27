#ifndef RULE_CLASS
#define RULE_CLASS

#include <string>
#include <vector>
#include <map>

class Rule;
typedef std::vector<Rule>          Rules;
typedef std::map<const char, int>  Adjacency;
typedef std::vector<char>    Expression;


enum stringPart {
	FULL_STRING  = 0,
	LEFT_PART    = 1,
	INFERENCE    = 2,
	RIGHT_PART   = 3,
};

enum rulesPart {
	UNUSED      = 0,
	LEFT_SIDE   = 1,
	RIGHT_SIDE  = 2,
};



enum eInference {
    THEN,           // =>
    IF_AND_ONLY_IF, // <=>
};

class Rule {
public:

	// constructor/destructor
	Rule(void);
	Rule(std::string left, std::string inference, std::string right);
	Rule(Rule const & rule);
	~Rule(void);
	Rule & operator=(Rule const & rvl);

	// member function
//	std::string const 		toString(void) const;

	std::string const & getLeft() const;
	eInference const &  getInference() const;
	std::string const & getRight() const;
	Adjacency const &   getAdjacency() const;

	Expression const &  getExpressionLeft() const;
	Expression const &  getExpressionRight() const;

	std::string const & getleftPostfix_() const;
	std::string         getRightPostfix_() const;

private:
	std::string left_;
	eInference inference_;
	std::string right_;

	std::string leftPostfix_;
	std::string rightPostfix_; /*uncomplete*/



	Adjacency adjacency_;



	Expression expressionLeft_;
	Expression expressionRight_;



	void createAdjacency();
	void createExpression();

	eInference initInference(std::string & inference);




//validation
	void validateExpresion(std::string &str);

	void HACK_checkOperators(std::string &str);

//	= delete;
};

std::ostream & operator << (std::ostream & o, Rule const & rhs);

#endif /*RULE_CLASS*/
