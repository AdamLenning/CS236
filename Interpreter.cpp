#include "Interpreter.h"

Interpreter::Interpreter(Parser* p) {
	parser = p; //This should be a parser that has already populated
	addRelations();
}

void Interpreter::addRelations() {
	std::vector<Predicate> schemes = parser->getSchemes();
	for (auto& scheme : schemes) {

		//Creates a new relation for a scheme
		Relation r(scheme.getID(), Tuple(scheme.getParameters())); 

		//Adds facts for a given relation
		for (auto& fact : parser->getFacts()) {
			if (fact.getID() == r.getName()) {
				r.addTuple(fact.getParameters());
			}
		}

		//Inserts the new relation into the map
		database.insert(std::pair<std::string, Relation>(scheme.getID(), r));
	}
}

void Interpreter::evaluateQueries() {
	for (auto& query : parser->getQueries()) {
		//Copies the relation from the database
		Relation r = database.at(query.getID());
		r.query(Tuple(query.getParameters()));
	}
}