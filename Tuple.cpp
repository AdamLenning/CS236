#include "Tuple.h"

Tuple::Tuple() {}

Tuple::Tuple(std::vector<Parameter> init) {
	for(unsigned i = 0; i < init.size(); i++){
		this->push_back(init.at(i).toString());
	}
}

int Tuple::getColumn(std::string columnName) {
	for (unsigned i = 0; i < this->size(); i++) {
		if (columnName == this->at(i)) {
			return i;
		}
	}
	return -1;
}

std::string Tuple::toString() {
	std::string returnString = "(";
	for (unsigned i = 0; i < this->size(); i++) {
		returnString.append(this->at(i));
		returnString.append(",");
	}
	returnString.pop_back();
	returnString.append(")");
	return returnString;
}