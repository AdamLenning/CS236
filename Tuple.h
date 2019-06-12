#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>
#include "Parameter.h"
#include "Predicate.h"

class Tuple : public std::vector<std::string> {
public:
	Tuple();
	Tuple(std::vector<Parameter> init);
	int getColumn(std::string columnName);
	std::string toString();
};

#endif // !TUPLE_H
