#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
	std::string id;
	std::vector<Parameter> parameters;
public:
	Predicate(std::string id, std::vector<Parameter>& params);
	Predicate(std::string id);
	Predicate();
	void add(Parameter p);
	std::string toString();
	std::vector<Parameter> getParameters();
	std::string getID();
};

#endif // !PREDICATE_H
