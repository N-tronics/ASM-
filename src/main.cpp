#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "include/lexer.h"
#include "include/error.h"
using namespace std;

ostream  &operator << (ostream &out, Token &tok) {
	if (tok.value == "\0"){
		out << tok.type;
	} else {
		out << tok.type << ":" << tok.value;
	}

	return out;
}

vector<string> read_file(string asms_file) { 
	ifstream file(asms_file);
	string cmd;
	vector<string> cmds;
	while (getline(file, cmd))
		cmds.push_back(cmd);

	return cmds;
}

int main(int argc, char **argv) {
	
	vector<string> cmds = read_file(argv[1]);
	Lexer lex;
	vector<vector<Token>> tokens;

	int line_number = 0;
	for (string cmd : cmds) {
		lex.set_cmd(cmd);
		bool success = lex.make_tokens(tokens);
		line_number++;
	}

	for (vector<Token> line : tokens) {
		for (Token tok : line)
			cout << tok << " ";
		cout << endl;
	}
}