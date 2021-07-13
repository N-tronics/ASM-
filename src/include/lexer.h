#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
using namespace std;

// TOKENS
const string INT 			= "INT";
const string KEYW			= "KEYW";
const string DIGITS			= "0123456789";
const string ALPHA			= "abcdefghijklmnopqrstuvwxyz";
const vector<char> WSPACE	= {' ', '\t', '\n', '\0'};
const vector<string> KEYWS {
	"lda", "out", "push", "pull", "sum", "ldb", "ldc", "ldo",
	"lds", "sreg", "areg", "breg", "creg", "oreg", "inc", "dec"
};
const vector<char> IGNORE = {
	'/'
};

struct Token { 
	string type;
	string value="\0";
};

class Lexer {
	string cmd;
	char current_char;
	int idx, line = 0;
	void reset();
public:
	Lexer() {
		reset();
		advance();
	}
	void set_cmd(string cmd_);
	void advance();
	void make_tokens(vector<vector<Token>> &toks);
	Token make_number();
	Token make_keyw();
};

template<typename T=char, typename C=string>
bool is_in(T c, C s);

#endif