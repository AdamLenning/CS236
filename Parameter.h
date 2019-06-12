#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

class Parameter{
private:
	std::string idOrString;
public:
	Parameter(std::string initializer);
	Parameter();
	std::string toString();
};

#endif // !PAREMETER_H
