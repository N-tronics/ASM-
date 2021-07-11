#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
using namespace std;

// TOKENS
const string HASH 			= "HASH";
const string ASTER 			= "ASTER";
const string LSQR 			= "LSQR";
const string RSQR 			= "RSQR";
const string INT 			= "INT";
const string FLOAT			= "FLOAT";
const string KEYW			= "KEYW";
const string DIGITS			= "0123456789";
const string ALPHA			= "abcdefghijklmnopqrstuvwxyz";
const vector<char> WSPACE	= {' ', '\t', '\n', '\0'};
const vector<string> KEYWS {
	"lda", "out", "push", "pull", "sum", "ldb", "ldc", "a", "b" , "c"
};


class Token {
public:
	string type, value;

	Token(string type_, string value_="\0") {
		this->type = type_;
		this->value = value_;
	}
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
	bool make_tokens(vector<vector<Token>> &toks);
	Token make_number();
	Token make_keyw();
};

template<typename T=char, typename C=string>
bool is_in(T c, C s);

#endif