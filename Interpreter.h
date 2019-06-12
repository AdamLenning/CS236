#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include "Relation.h"
#include "Parser.h"

class Interpreter {
private:
	std::map<std::string, Relation> database; //remember that map sorts by string so the output might not be valid
	Parser* parser;
	void addRelations();

public:
	Interpreter(Parser* p);
	void evaluateQueries();
};

#endif