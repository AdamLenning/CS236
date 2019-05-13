#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

enum Token {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD,
	SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, MEOF
};

static int lineNum;
static int totalTokens;

class Lexer {
	
public: 
 
	Lexer(string& input) : input(input) {
		lineNum = 1;
		totalTokens = 1;
		automata.push_back(new StringMatch(",", COMMA));
		automata.push_back(new StringMatch(".", PERIOD));
		automata.push_back(new StringMatch("?", Q_MARK));
		automata.push_back(new StringMatch("(", LEFT_PAREN));
		automata.push_back(new StringMatch(")", RIGHT_PAREN));
		automata.push_back(new Colon());
		automata.push_back(new StringMatch("*", MULTIPLY));
		automata.push_back(new StringMatch("+", ADD));
		automata.push_back(new StringMatch("Schemes", SCHEMES));
		automata.push_back(new StringMatch("Facts", FACTS));
		automata.push_back(new StringMatch("Rules", RULES));
		automata.push_back(new StringMatch("Queries", QUERIES));
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

	static string toString(Token t) {
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
		case FACTS: return ("FACTS");
		case RULES: return ("RULES");
		case QUERIES: return ("QUERIES");
		case ID: return ("ID");
		case STRING: return ("STRING");
		case COMMENT: return ("COMMENT");
		case WHITESPACE: return ("WHITESPACE");
		case UNDEFINED: return ("UNDEFINED");
		case MEOF: return ("MEOF");
		default: break;
		}
		return ("Uh oh!");
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
				totalTokens++;
			}
			else {
				cout << "Bad (" << input.front() << ")" << endl;
				input.erase(0);
				totalTokens++;
			}
		}
		cout << "Total Tokens: " << totalTokens << endl;
	}

	class Automaton {
	public:
		virtual ~Automaton() {}
		virtual int read(const string& input) const = 0;
		virtual Token makeToken(const string& s) const = 0;
	};

	class StringMatch : public Automaton {
		string stringToMatch;
		Token tokenToMake;

	public:

		StringMatch(const string& s, Token t) :
			stringToMatch(s), tokenToMake(t) {
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
			cout <<  "(" << toString(tokenToMake) << ",\"" << s << "\"," << lineNum << ")" << endl;
			return tokenToMake;
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
				cout <<  "(" << toString(COLON_DASH) << "\":-\"" << lineNum << ")" << endl;
				return COLON_DASH;
			}
			else if (s[0] == ':') {
				cout << "(" << toString(COLON) << "\":\"" << lineNum << ")" << endl;
				return COLON;
			}
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
			return WHITESPACE;
		}
	};

	class Identifier : public Automaton {

		int s0(int i, const string& input) const {
			const auto& c = input[i];
			if (i < input.size() && isalpha(c)) {
				return s1(++i, input);
			}

			return 0;
		}

		int s1(int i, const string& input) const {
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
			cout << "(" << toString(ID) << ",\"" << s << "\"," << lineNum << ")" << endl;
			return ID;
		}
	};

	class Comment : public Automaton {
		int s0(int i, const string& input) const {
			const auto& c = input[i];
			if (c == '\0') return i;
			if (c == '\n') return i;
			else return s0(++i, input);
		}
	public:
		int read(const string& input) const {
			int i = 0;
			if (input[0] == '#') {
				return s0(++i, input);
			}
			return 0;
		}

		Token makeToken(const string& s) const {
			cout << "(" << toString(COMMENT) << ",\"" << s << "\"," << lineNum << ")" << endl;
			return COMMENT;
		}
	};

	class String : public Automaton {
		int s0(int i, const string& input) const {
			const auto& c = input[i];
			if (c == '\'') return ++i;
			else return s0(++i, input);
		}
	public:
		int read(const string& input) const {
			int i = 0;
			if (input[0] == '\'') {
				return s0(++i, input);
			}
			return 0;
		}

		Token makeToken(const string& s) const {
			cout << "(" << toString(STRING) << ",\"" << s << "\"," << lineNum << ")" << endl;
			return STRING;
		}
	};

private:
	vector<Automaton*> automata;
	string& input;
};

