#include "Lexer.cpp"

int main(int argc, char* argv[]) {
	ifstream ifs(argv[1]);
	string input((istreambuf_iterator<char>(ifs)),
		(istreambuf_iterator<char>()));
	cout << "Input:" << endl << input << endl;

	Lexer lex(input);
	lex.generateTokens();

	return 0;
}