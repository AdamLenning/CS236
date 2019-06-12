#include "Rule.h"

Rule::Rule(Predicate head, Predicate p1) {
	headPredicate = head;
	predicateList.push_back(p1);
}

Rule::Rule(Predicate head) {
	headPredicate = head;
}

void Rule::add(Predicate p) {
	predicateList.push_back(p);
}

std::string Rule::toString() {
	std::string returnString = headPredicate.toString() + " :- ";
	for (auto& pred : predicateList) {
		returnString += pred.toString() + ",";
	}
	returnString.pop_back();
	returnString += ".";
	return returnString;
}