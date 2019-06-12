#include "Predicate.h"

Predicate::Predicate(std::string id, std::vector<Parameter>& params) {
	this->id = id;
	this->parameters = params;
}

Predicate::Predicate(std::string id) {
	this->id = id;
}

Predicate::Predicate() {
	id = "uh oh!";
}

void Predicate::add(Parameter p) {
	parameters.push_back(p);
}

std::string Predicate::toString() {
	std::string returnString = id + "(";
	for (auto& param : parameters) {
		returnString += param.toString();
		returnString += ",";
	}
	returnString.pop_back();
	returnString += ")";
	return returnString;
}

std::vector<Parameter> Predicate::getParameters() {
	return parameters;
}

std::string Predicate::getID() {
	return id;
}