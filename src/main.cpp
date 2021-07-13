#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "include/lexer.h"
#include "include/error.h"
#include "include/cpu.h"
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

	for (string cmd : cmds) {
		lex.set_cmd(cmd);
		lex.make_tokens(tokens);
	}
	Interpreter interpret(tokens);
}