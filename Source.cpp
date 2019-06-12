#include "Lexer.cpp"
#include "Parser.h"
#include "Interpreter.h"
#include <cstring>

int main(int argc, char* argv[]) {
	/*ifstream ifs(argv[1]);
	string input((istreambuf_iterator<char>(ifs)),
		(istreambuf_iterator<char>()));

	Lexer lex(input);
	lex.generateTokens();

	Parser parser(lex.getTokens());
	parser.parse();

	Interpreter i(&parser);
	i.evaluateQueries();*/

	vector<Parameter> schemeA;
	schemeA.push_back(Parameter("cat"));
	schemeA.push_back(Parameter("dog"));
	schemeA.push_back(Parameter("fish"));

	Relation a("a", Tuple(schemeA));

	vector<Parameter> schemeB;
	schemeB.push_back(Parameter("cat"));
	schemeB.push_back(Parameter("fish"));
	schemeB.push_back(Parameter("bird"));
	schemeB.push_back(Parameter("bunny"));

	Relation b("b", Tuple(schemeB));

	a.join(b);

	/*vector<Parameter> fact1;
	fact1.push_back(Parameter("'1'"));
	fact1.push_back(Parameter("'Adam'"));
	fact1.push_back(Parameter("'123 Address'"));
	fact1.push_back(Parameter("'1'"));
	r.addTuple(Tuple(fact1));

	vector<Parameter> fact2;
	fact2.push_back(Parameter("'2'"));
	fact2.push_back(Parameter("'Adam'"));
	fact2.push_back(Parameter("'124 Address'"));
	fact2.push_back(Parameter("'222-2222'"));
	r.addTuple(Tuple(fact2));

	vector<Parameter> fact3;
	fact3.push_back(Parameter("'3'"));
	fact3.push_back(Parameter("'Joe'"));
	fact3.push_back(Parameter("'123 Address'"));
	fact3.push_back(Parameter("'3'"));
	r.addTuple(Tuple(fact3));

	if (!std::strcmp(argv[2], "query1")) {
		vector<Parameter> q1;
		q1.push_back(Parameter("'1'"));
		q1.push_back(Parameter("A"));
		q1.push_back(Parameter("B"));
		q1.push_back(Parameter("C"));
		r.query(Tuple(q1));
		cout << "pass" << endl << endl;
	} else if (!std::strcmp(argv[2], "query2")) {
		vector<Parameter> q2;
		q2.push_back(Parameter("A"));
		q2.push_back(Parameter("C"));
		q2.push_back(Parameter("B"));
		q2.push_back(Parameter("A"));
		r.query(Tuple(q2));
		cout << "pass" << endl << endl;

	} else if (!std::strcmp(argv[2], "query3")) {
		vector<Parameter> q3;
		q3.push_back(Parameter("D"));
		q3.push_back(Parameter("A"));
		q3.push_back(Parameter("B"));
		q3.push_back(Parameter("C"));
		r.query(Tuple(q3));
		cout << "pass" << endl << endl;

	} else if (!std::strcmp(argv[2], "query4")) {
		vector<Parameter> q4;
		q4.push_back(Parameter("'4'"));
		q4.push_back(Parameter("A"));
		q4.push_back(Parameter("B"));
		q4.push_back(Parameter("C"));
		r.query(Tuple(q4));
		cout << "pass" << endl << endl;

	} else if (!std::strcmp(argv[2], "rename")) {
		r.rename("S", "Q");
		cout << r.toString();
		cout << "pass" << endl << endl;

	} else if (!std::strcmp(argv[2], "project")) {
		vector<int> projection{ 2 , 0 };	
		r.project(projection);
		cout << r.toString();
		cout << "pass" << endl << endl;

	} else if (!std::strcmp(argv[2],"select1-1")) { //Returns a set of 2
		r.select1("N", "'Adam'");
		cout << r.toString();
		cout << "pass" << endl << endl;

	} else if (!std::strcmp(argv[2], "select1-2")) { //Returns an empty set
		r.select1("S", "'4'");
		cout << r.toString();
		cout << "pass" << endl << endl;

	} else if (!std::strcmp(argv[2], "select2-1")) { //Returns a set of 2
		//r.select2("S", "P");
		cout << r.toString();
		cout << "pass" << endl << endl;

	} else if (!std::strcmp(argv[2], "select2-2")) { //Returns an empty set
		//r.select2("S", "N");
		cout << r.toString();
		cout << "pass" << endl << endl;
	}*/

	return 0;
}