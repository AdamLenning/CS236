#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>
#include <set>
#include "Token.h"
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"

class Parser {
private:
	std::vector<Token>& input;
	std::vector<Predicate> facts;
	std::vector<Predicate> schemes;
	std::vector<Rule> rules;
	std::vector<Predicate> queries;
	std::set<std::string> domain;
	int index;

	void datalogProgram();
	void schemeList(std::vector<Predicate>& schemesL);
	Predicate scheme();
	void idList(Predicate& p);
	Predicate fact();
	void factList(std::vector<Predicate>& factsL);
	Rule rule();
	void ruleList(std::vector<Rule>& rulesL);
	Predicate headPredicate();
	Predicate predicate();
	void predicateList(Rule& r);
	Parameter parameter();
	void parameterList(Predicate& p);
	Parameter expression();
	std::string myOperator();
	Predicate query();
	void queryList(std::vector<Predicate>& queriesL);
	void stringList(Predicate& p);
	void populateDomain();

public:
	Parser(std::vector<Token>& input);
	void parse();
	std::vector<Predicate>& getFacts();
	std::vector<Predicate>& getSchemes();
	std::vector<Rule>& getRules();
	std::vector<Predicate>& getQueries();
};

#endif // !PARSER_H

