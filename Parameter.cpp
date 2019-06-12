#include "Parameter.h"

Parameter::Parameter(std::string initializer) {
	this->idOrString = initializer;
}

Parameter::Parameter() {
	this->idOrString = "uh oh!";
}

std::string Parameter::toString() {
	return idOrString;
}