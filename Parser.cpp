#include "Parser.h"

Parser::Parser(std::vector<Token>& input) : input(input), index(0) {}

void Parser::parse() {
	try {
		datalogProgram();
		/*std::cout << "Success!" << std::endl;
		std::cout << "Schemes(" << schemes.size() << "):" << std::endl;
		for (unsigned int i = 0; i < schemes.size(); i++) {
			std::cout << "  " << schemes.at(i).toString() << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Facts(" << facts.size() << "):" << std::endl;
		for (unsigned int i = 0; i < facts.size(); i++) {
			std::cout << "  " << facts.at(i).toString() << "." << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Rules(" << rules.size() << "):" << std::endl;
		for (unsigned int i = 0; i < rules.size(); i++) {
			std::cout << "  " << rules.at(i).toString() << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Queries(" << queries.size() << "):" << std::endl;
		for (unsigned int i = 0; i < queries.size(); i++) {
			std::cout << "  " << queries.at(i).toString() <<  "?" << std::endl;
		}
		std::cout << std::endl;
		populateDomain(); //Populates the domain by searching through facts
		std::cout << "Domain(" << domain.size() <<"):" << std::endl;
		for (auto& string : domain) {
			std::cout << "  " << string << std::endl;
		}*/
	} 
	catch (Token t) {
		std::cout << "Failure!\n\t" << t.toString();
	}
}

void Parser::datalogProgram() {
	switch (input.at(index).getType()) {
	case SCHEMES:
		if (input.at(index + 1).getType() != COLON) throw input.at(index + 1); 
		index++;
		schemes.push_back(scheme());
		schemeList(schemes);
		if (input.at(index + 1).getType() != FACTS) throw input.at(index + 1);
		index++;
		if (input.at(index + 1).getType() != COLON) throw input.at(index + 1);
		index++;
		factList(facts);
		if (input.at(index + 1).getType() != RULES) throw input.at(index + 1);
		index++;
		if (input.at(index + 1).getType() != COLON) throw input.at(index + 1);
		index++;
		ruleList(rules);
		if (input.at(index + 1).getType() != QUERIES) throw input.at(index + 1);
		index++;
		if (input.at(index + 1).getType() != COLON) throw input.at(index + 1);
		index++;
		queries.push_back(query());
		queryList(queries);
		if (input.at(index + 1).getType() != MEOF) throw input.at(index + 1);
		return;
	case MEOF: return;
	default: throw input.at(index);
	}
}

Predicate Parser::scheme() {
	switch (input.at(index + 1).getType()){
	case ID: {
		index++;
		Predicate pred(input.at(index).getValue());
		if (input.at(index + 1).getType() != LEFT_PAREN) throw input.at(index + 1);
		index++;
		if (input.at(index + 1).getType() != ID) throw input.at(index + 1);
		index++;
		pred.add(Parameter(input.at(index).getValue()));
		idList(pred);
		if (input.at(index + 1).getType() != RIGHT_PAREN) throw input.at(index + 1);
		index++;
		return pred;
	}
	default: throw input.at(index + 1);
	}
}

void Parser::schemeList(std::vector<Predicate>& preds) {
	switch (input.at(index + 1).getType()) {
	case ID:
		preds.push_back(scheme());
		schemeList(preds);
		return;
	case FACTS:
		return;
	default: throw input.at(index + 1);
	}
}

void Parser::idList(Predicate& p) {
	switch (input.at(index + 1).getType()) {
	case COMMA:
		index++;
		if (input.at(index + 1).getType() != ID) throw input.at(index + 1);
		index++;
		p.add(Parameter(input.at(index).getValue()));
		idList(p);
		return;
	case RIGHT_PAREN:
		return;
	default: throw input.at(index + 1);
	}
}

Predicate Parser::fact() {
	switch (input.at(index + 1).getType()) {
	case ID: {
		index++;
		Predicate pred(input.at(index).getValue());
		if (input.at(index + 1).getType() != LEFT_PAREN) throw input.at(index + 1);
		index++;
		if (input.at(index + 1).getType() != STRING) throw input.at(index + 1);
		index++;
		pred.add(Parameter(input.at(index).getValue()));
		stringList(pred);
		if (input.at(index + 1).getType() != RIGHT_PAREN) throw input.at(index + 1);
		index++;
		if (input.at(index + 1).getType() != PERIOD) throw input.at(index + 1);
		index++;
		return pred;
	}
	default: throw input.at(index + 1);
	}
}

void Parser::factList(std::vector<Predicate>& preds) {
	switch (input.at(index + 1).getType()) {
	case ID:
		preds.push_back(fact());
		factList(preds);
		return;
	case RULES:
		return;
	default: throw input.at(index + 1);
	}
}

Rule Parser::rule() {
	switch (input.at(index + 1).getType()) {
	case ID: {
		Rule rule(headPredicate());
		if (input.at(index + 1).getType() != COLON_DASH) throw input.at(index + 1);
		index++;
		rule.add(predicate());
		predicateList(rule);
		if (input.at(index + 1).getType() != PERIOD) throw input.at(index + 1);
		index++;
		return rule;
	}
	default: throw input.at(index + 1);
	}
}

void Parser::ruleList(std::vector<Rule>& r) {
	switch (input.at(index + 1).getType()) {
	case ID:
		r.push_back(rule());
		ruleList(r);
		return;
	case QUERIES:
		return;
	default: throw input.at(index + 1);
	}
}

Predicate Parser::headPredicate() {
	switch (input.at(index + 1).getType()) {
	case ID: {
		index++;
		Predicate p(input.at(index).getValue());
		if (input.at(index + 1).getType() != LEFT_PAREN) throw input.at(index + 1);
		index++;
		if (input.at(index + 1).getType() != ID) throw input.at(index + 1);
		index++;
		p.add(Parameter(input.at(index).getValue()));
		idList(p);
		if (input.at(index + 1).getType() != RIGHT_PAREN) throw input.at(index + 1);
		index++;
		return p;
	}
	default: throw input.at(index + 1);
	}
}

Predicate Parser::predicate() {
	switch (input.at(index + 1).getType()) {
	case ID: {
		index++;
		Predicate pred(input.at(index).getValue());
		if (input.at(index + 1).getType() != LEFT_PAREN) throw input.at(index + 1);
		index++;
		pred.add(parameter());
		parameterList(pred);
		if (input.at(index + 1).getType() != RIGHT_PAREN) throw input.at(index + 1);
		index++;
		return pred; 
	}
	default: throw input.at(index + 1);
	}
}

void Parser::predicateList(Rule& r) {
	switch (input.at(index + 1).getType()) {
	case COMMA:
		index++;
		r.add(predicate());
		predicateList(r);
		return;
	case PERIOD:
		return;
	default: throw input.at(index + 1);
	}
}

Parameter Parser::parameter() {
	switch (input.at(index + 1).getType()) {
	case ID:
		index++;
		return Parameter(input.at(index).getValue());
	case STRING:
		index++;
		return Parameter(input.at(index).getValue());
	case LEFT_PAREN:
		return expression();
	default: throw input.at(index + 1);
	}
}

void Parser::parameterList(Predicate& p) {
	switch (input.at(index + 1).getType()) {
	case COMMA:
		index++;
		p.add(parameter());
		parameterList(p);
		return;
	case RIGHT_PAREN:
		return;
	default: throw input.at(index + 1);
	}
}

Parameter Parser::expression() {
	switch (input.at(index + 1).getType()) {
	case LEFT_PAREN: {
		index++;
		std::string param = input.at(index).getValue();
		Parameter p1 = parameter();
		param.append(p1.toString());
		param.append(myOperator());
		Parameter p2 = parameter();
		param.append(p2.toString());
		if (input.at(index + 1).getType() != RIGHT_PAREN) throw input.at(index + 1);
		index++;
		param.append(input.at(index).getValue());
		return param;
	}
	default: throw input.at(index + 1);
	}
}

std::string Parser::myOperator() {
	switch (input.at(index + 1).getType()) {
	case ADD:
		index++;
		return "+";
	case MULTIPLY:
		index++;
		return "*";
	default: throw input.at(index + 1);
	}
}

Predicate Parser::query() {
	switch (input.at(index + 1).getType()) {
	case ID:
	{
		Predicate p = predicate();
		if (input.at(index + 1).getType() != Q_MARK) throw input.at(index + 1);
		index++;
		return p;
	}
	default: throw input.at(index + 1);
	}
}

void Parser::queryList(std::vector<Predicate>& preds) {
	switch (input.at(index + 1).getType()) {
	case ID:
		preds.push_back(query());
		queryList(preds);
		return;
	case MEOF:
		return;
	default: throw input.at(index + 1);
	}
}

void Parser::stringList(Predicate& p) {
	switch (input.at(index + 1).getType()) {
	case COMMA:
		index++;
		if (input.at(index + 1).getType() != STRING) throw input.at(index + 1);
		index++;
		p.add(Parameter(input.at(index).getValue()));
		stringList(p);
		return;
	case RIGHT_PAREN:
		return;
	default: throw input.at(index + 1);
	}
}

void Parser::populateDomain() {
	for (auto& fact : facts) {
		for (auto& string : fact.getParameters()) {
			domain.insert(string.toString());
		}
	}
}

std::vector<Predicate>& Parser::getFacts() {
	return facts;
}

std::vector<Predicate>& Parser::getSchemes() {
	return schemes;
}

std::vector<Rule>& Parser::getRules() {
	return rules;
}

std::vector<Predicate>& Parser::getQueries() {
	return queries;
}