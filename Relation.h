#ifndef RELATION_H
#define RELATION_H

#include "Tuple.h"
#include <set>
#include <iostream>
#include <algorithm>

class Relation {
private:
	std::string name;
	Tuple scheme;
	std::set<Tuple> r;
public:
	Relation(std::string name, Tuple scheme);
	void addTuple(Tuple t);
	std::string getName();
	std::string toString();
	void select1(std::string columnName, std::string stringMatch);
	void select2(int column1, int column2);
	void project(std::vector<int> columns);
	void rename(std::string columnName, std::string newName);
	void query(Tuple tuplesToFind);
	Relation join(Relation b);
	void unionize(Relation b);
};

#endif // !RELATION_H

