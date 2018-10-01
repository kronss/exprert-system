#ifndef RULE_CLASS
#define RULE_CLASS

#include <string>
#include <list>

class Rule;

enum eInference {
    THEN,           // =>
    IF_AND_ONLY_IF, // <=>
};

typedef std::list<Rule> Rules;

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
	eInference const & getInference() const;
	std::string const & getRight() const;

//	void 					setLeft(std::string const & left) { left_ = left; }
//	void 					setRight(std::string const & right) { right_ = right; }

//	Fact 					solve(Facts facts);

private:
	std::string left_;
	eInference inference_;
	std::string right_;



//	= delete;
};

// stream overload
//std::ostream & 	operator<<(std::ostream & o, Rule const & rule);
//bool			operator==(Rule const lhs, Rule const rhs);

#endif /*RULE_CLASS*/
