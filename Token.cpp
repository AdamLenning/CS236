#include "Token.h"

Token::Token() {
	t = UNDEFINED;
	lineNum = 0;
}

Token::Token(TokenType t, std::string value, int lineNum) {
	this->t = t;
	this->value = value;
	this->lineNum = lineNum;
}

TokenType Token::getType() {
	return t;
}

std::string Token::getValue() {
	return value;
}

int Token::getLineNum() {
	return lineNum;
}

std::string Token::toString() {
	std::string s = "(" + enumToString(t) + ",\"" + value + "\"," + std::to_string(lineNum) + ")\n";
	return s;
}

std::string Token::enumToString(TokenType t) {
	switch (t) {
	case COMMA: return ("COMMA");
	case PERIOD: return ("PERIOD");
	case Q_MARK: return ("Q_MARK");
	case LEFT_PAREN: return ("LEFT_PAREN");
	case RIGHT_PAREN: return ("RIGHT_PAREN");
	case COLON: return ("COLON");
	case COLON_DASH: return ("COLON_DASH");
	case MULTIPLY: return ("MULTIPLY");
	case ADD: return ("ADD");
	case SCHEMES: return ("SCHEMES");
	case FACTS: return("FACTS");
	case RULES: return("RULES");
	case QUERIES: return("QUERIES");
	case ID: return ("ID");
	case STRING: return ("STRING");
	case COMMENT: return ("COMMENT");
	case WHITESPACE: return ("WHITESPACE");
	case UNDEFINED: return ("UNDEFINED");
	case MEOF: return ("EOF");
	default: break;
	}
	return ("Uh oh!");
}

