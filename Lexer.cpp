#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Token.h"
using namespace std;

static int lineNum;
static int tempLineNum;
static bool isSingleLineUnterminatingBlock;

class Lexer {
	
public: 
 
	Lexer(string& input) : input(input) {
		lineNum = 1;
		isSingleLineUnterminatingBlock = false;
		automata.push_back(new StringMatch(",", COMMA));
		automata.push_back(new StringMatch(".", PERIOD));
		automata.push_back(new StringMatch("?", Q_MARK));
		automata.push_back(new StringMatch("(", LEFT_PAREN));
		automata.push_back(new StringMatch(")", RIGHT_PAREN));
		automata.push_back(new Colon());
		automata.push_back(new StringMatch("*", MULTIPLY));
		automata.push_back(new StringMatch("+", ADD));
		automata.push_back(new Identifier());
		automata.push_back(new String());
		automata.push_back(new Comment());
		automata.push_back(new Whitespace());
	}

	~Lexer() {
		for (auto a : automata) {
			delete a;
		}
	}

	void generateTokens() {
		int maxRead = 0;
		Token maxToken;
		while (input.size() > 0) {
			for (auto& automaton : automata) {
				int read = automaton->read(input);
				if (read > maxRead) {
					maxRead = read;
					maxToken = automaton->makeToken(input.substr(0, maxRead));
				}
			}
			if (maxRead > 0) {
				input.erase(0, maxRead);
				maxRead = 0;
				if(maxToken.getType() != WHITESPACE && maxToken.getType() != COMMENT) tokens.push_back(maxToken);
			}
			else {
				string s = "";
				s += input.at(0);
				tokens.push_back(Token(UNDEFINED, s, lineNum));
				input.erase(0,1);
			}
		}
		tokens.push_back(Token(MEOF, "EOF", lineNum));
		/*for (size_t i = 0; i < tokens.size(); i++) {
			cout << tokens.at(i).toString();
		}
		cout << "Total Tokens = " << tokens.size() << endl;*/
	}
	
	vector<Token>& getTokens() {
		return tokens;
	}

	class Automaton {
	public:
		virtual ~Automaton() {}
		virtual int read(const string& input) const = 0;
		virtual Token makeToken(const string& s) const = 0;
	};

	class StringMatch : public Automaton {
		string stringToMatch;
		TokenType tokenToMake;

	public:

		StringMatch(const string& s, TokenType t){
			stringToMatch = s;
			tokenToMake = t;
		}
		
		int read(const string& input) const {
			if (input.size() < stringToMatch.size()) {
				return 0;
			}

			int i = 0;
			for (const auto& c : stringToMatch) {
				if (c != input[i]) {
					return 0;
				}
				++i;
			}
			return stringToMatch.size();
		}

		Token makeToken(const string& s) const {
			return Token(tokenToMake, s, lineNum);
		}
	};

	class Colon : public Automaton {
	public:
		int read(const string& input) const {
			if (input[0] == ':' && input[1] == '-') return 2;
			else if (input[0] == ':') return 1;
			else return 0;
		}

		Token makeToken(const string & s) const {
			if (s[0] == ':' && s[1] == '-') {
				return Token(COLON_DASH, ":-", lineNum);
			}
			else if (s[0] == ':') {
				return Token(COLON, ":", lineNum);
			}
			else return Token(UNDEFINED, s, lineNum);
		}
	};

	class Whitespace : public Automaton {
	public:
		int read(const string& input) const {
			int i = 0;
			while (isspace(input[i])) {
				if (input[i] == '\n') lineNum++;
				++i;
			}
			return i;
		}

		Token makeToken(const string& s) const {
			return Token(WHITESPACE, s, lineNum);
		}
	};

	class Identifier : public Automaton {

		int s0(size_t i, const string& input) const {
			const auto& c = input[i];
			if (i < input.size() && isalpha(c)) {
				return s1(++i, input);
			}

			return 0;
		}

		int s1(size_t i, const string& input) const {
			const auto& c = input[i];
			if (i < input.size() && (isalpha(c) || isdigit(c))) {
				return s1(++i, input);
			}

			return i;
		}

	public:

		int read(const string& input) const {
			return s0(0, input);
		}

		Token makeToken(const string& s) const {
			if (s == "Schemes") {
				return Token(SCHEMES, s, lineNum);
			}
			else if (s == "Facts") {
				return Token(FACTS, s, lineNum);
			}
			else if (s == "Rules") {
				return Token(RULES, s, lineNum);
			}
			else if (s == "Queries") {
				return Token(QUERIES, s, lineNum);
			}
			else {
				return Token(ID, s, lineNum);
			}
		}
	};

	class Comment : public Automaton {
		int s0(int i, const string& input) const {
			const auto& c = input[i];
			if (c == '\0') return i;
			if (c == '\n') return i;
			if (c == '|' && input[i-1] == '#') return s1(++i, input);
			else return s0(++i, input);
		}
		int s1(int i, const string& input) const {
			const auto& c = input[i];
			if (c == '\0') {
				return i;
			}
			if (c == '\n') {
				tempLineNum++;
				lineNum++;
			}
			if (c == '|') return s2(++i, input);
			else return s1(++i, input);
		}
		int s2(int i, const string& input) const {
			const auto& c = input[i];
			if (c == '\0') return i;
			if (c == '#' && input[i-1] == '|') return ++i;
			if (c == '\n') {
				tempLineNum++;
				lineNum++; 
				return s1(++i, input);
			}
			else return s1(++i, input);
		}
	public:
		int read(const string& input) const {
			tempLineNum = 0;
			int i = 0;
			if (input[0] == '#') {
				return s0(++i, input);
			}
			return 0;
		}

		Token makeToken(const string& s) const {
			string sub;
			if (s.length() > 1) {
				sub = s.substr(s.size() - 2, s.size() - 1);
			}
			else {
				sub == "I can write anything here that isnt't a newline I think!";
			}
			if (((tempLineNum > 0)/* || isSingleLineUnterminatingBlockComment*/) && (sub != "|#")) {
				return Token(UNDEFINED, s, lineNum - tempLineNum);
			}
			return Token(COMMENT, s, lineNum - tempLineNum);
		}
	};

	class String : public Automaton {

		int s0(int i, const string& input) const {
			const auto& c = input[i];
			if (c == '\'') return s1(++i, input);
			//else if (c == '\'') return i;
			if (c == '\n') {
				tempLineNum++;
				lineNum++;
			}
			else if (c == '\0') {
				return i;
			}
			return s0(++i, input);
		}

		int s1(int i, const string& input) const {
			const auto& c = input[i];
			if (c == '\0') return i;
			else if (c == '\'') return s0(++i, input);
			return i;
		}

	public:
		int read(const string& input) const {
			tempLineNum = 0;
			int i = 0;
			if (input[0] == '\'') {
				return s0(++i, input);
			}
			return 0;
		}

		Token makeToken(const string& s) const {
			auto& c = s.back();
			string sub;
			if (s.length() > 1) {
				sub = s.substr(s.size() - 2, s.size() - 1);
			}
			else {
				sub = "I can write anything here that isnt't a newline I think!";
			}
			if ((c != '\'') && (sub == "''")) {
				return Token(UNDEFINED, s, lineNum - tempLineNum);
			}
			return Token(STRING, s, lineNum - tempLineNum);
		}
	};

private:
	vector<Automaton*> automata;
	string& input;
	vector<Token> tokens;
};

