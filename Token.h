#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD,
	SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, MEOF
};

class Token {
private:
	TokenType t;
	std::string value;
	int lineNum;

public:
	Token();
	Token(TokenType t, std::string value, int lineNum);
	std::string getValue();
	TokenType getType();
	int getLineNum();
	std::string toString();
	std::string enumToString(TokenType t);
};

#endif // !TOKEN_H
