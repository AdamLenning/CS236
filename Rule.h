#ifndef RULE_H
#define RULE_H

#include "Predicate.h"

class Rule {
private:
	Predicate headPredicate;
	std::vector<Predicate> predicateList;
public:
	Rule(Predicate head, Predicate p1);
	Rule(Predicate head);
	void add(Predicate p);
	std::string toString();
};

#endif // !RULE_H

