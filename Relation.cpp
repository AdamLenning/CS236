#include "Relation.h"

Relation::Relation(std::string name, Tuple scheme) {
	this->name = name;
	this->scheme = scheme;
}

void Relation::addTuple(Tuple t) {
	r.insert(t);
}

std::string Relation::getName() {
	return name;
}

std::string Relation::toString() {

	std::string returnString;
	for (auto tuple : r) {
		for (unsigned i = 0; i < scheme.size(); i++) {
			returnString += scheme.at(i) + "=" + tuple.at(i) + ", ";
		}
		returnString.pop_back();
		returnString.pop_back();
		returnString += "\n";
	}
	return returnString;
}


void Relation::select1(std::string columnName, std::string stringMatch) {

	int columnIndex = scheme.getColumn(columnName);
	std::set<Tuple> newSet;
	for (auto t : r) {
		bool stringComp = (t.at(columnIndex) == stringMatch);
		if ((columnIndex != -1) && stringComp) {
			newSet.insert(t);
		}
	}
	r = newSet;
}

void Relation::select2(int column1, int column2) {	
	std::set<Tuple> newSet;
	for (auto t : r) {
		if (t.at(column1) == t.at(column2)) {
			newSet.insert(t);
		}
	}
	r = newSet;
}

void Relation::project(std::vector<int> columns) {
	
	Tuple newScheme;
	for (unsigned i = 0; i < columns.size(); i++) {
		newScheme.push_back(scheme.at(columns.at(i)));
	}
	scheme = newScheme;

	std::set<Tuple> newSet;
	for (auto t : r) {
		Tuple newTuple;
		for (unsigned i = 0; i < columns.size(); i++) {
			newTuple.push_back(t.at(columns.at(i)));
		}
		newSet.insert(newTuple);
	}
	r = newSet;
}

void Relation::rename(std::string columnName, std::string newName) {
	for (unsigned i = 0; i < scheme.size(); i++) {
		if (scheme.at(i) == columnName) {
			scheme.at(i) = newName;
		}
	}
}

void Relation::query(Tuple tuplesToFind) {
	
	std::vector<int> projectList;
	std::vector<std::string> newNames;

	//Perform the selects and mark what to keep for projects and rename
	for (unsigned i = 0; i < tuplesToFind.size(); i++) {
		
		//Finds the iterator in newNames if the parameter exists already, useful later on.
		std::vector<std::string>::iterator it = std::find(newNames.begin(), newNames.end(), tuplesToFind.at(i));
		
		//Checks if constant
		if (tuplesToFind.at(i).at(0) == '\'') {
			select1(scheme.at(i), tuplesToFind.at(i));
		}

		//If have seen the variable, the column where it was stored is in the map, saw an error on my script, but I'll have to check later
		else if (it != newNames.end()) {
			select2(std::distance(newNames.begin(), it), i); 
		}

		//adds to map if you haven't seen variable before
		else {
			newNames.push_back(tuplesToFind.at(i));
			projectList.push_back(i);
		}
	}

	project(projectList);

	std::string returnString;
	for (auto tuple : r) {
		returnString.append("  ");
		for (unsigned i = 0; i < scheme.size(); i++) {
			returnString += newNames.at(i) + "=" + tuple.at(i) + ", ";
		}
		if (returnString.size() != 0) {
			returnString.pop_back();
			returnString.pop_back();
			returnString += "\n";
		}
	}
	if (r.size() == 0) {
		std::cout << name << tuplesToFind.toString() << "? No" << std::endl;
	}
	else if(scheme.size() == 0) {
		std::cout << name << tuplesToFind.toString() << "? Yes(" << r.size() << ")"
			<< std::endl;
	}
	else {
		std::cout << name << tuplesToFind.toString() << "? Yes(" << r.size() << ")"
			<< std::endl << returnString;
	}
}

Relation Relation::join(Relation b) {
	
	std::vector<int> matchColumnsA;
	std::vector<int> matchColumnsB;

	//Add columns that match to data structure, works fine
	for (auto& column : scheme) {
		for (auto& columnB : b.scheme) {
			if (column == columnB) {
				matchColumnsA.push_back(scheme.getColumn(column));
				matchColumnsB.push_back(b.scheme.getColumn(columnB));
			}
		}
	}

	//Add columns that are unique to data structure

	//Combine schemes, then create return Relation

	//Loop Tuples and add to return Relation


}