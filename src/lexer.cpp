#include <string>
#include <vector>
#include <iostream>
#include "include/lexer.h"
#include "include/error.h"
using namespace std;

template<typename T=char, typename C=string>
bool is_in(T c, C s) {
	for (T sc : s)
		if (c == sc) return true;

	return false;
}

void Lexer::reset() {
    this->idx = -1;
    this->current_char = '\0';
    this->advance();
}

void Lexer::set_cmd(string cmd_) {
    this->cmd = cmd_;
    this->line++;
	this->reset();
}

void Lexer::advance() {
    if ((this->idx + 1) < this->cmd.length()) {
        this->idx++;
        this->current_char = this->cmd[idx];
    }
    else
        this->current_char = '\0';
}

bool Lexer::make_tokens(vector<vector<Token>> &toks) {
    vector<Token> statement;
    while (this->current_char != '\0') {
        if (is_in<char, vector<char>>(this->current_char, WSPACE))
            this->advance();
        else if (is_in(this->current_char, DIGITS + '.')) {
            statement.push_back(this->make_number());
        }
        else if (is_in(this->current_char, ALPHA)) {
            statement.push_back(this->make_keyw());
        }
        else if (current_char == '#') {
            statement.push_back(Token(HASH));
            this->advance();
        }
        else if (current_char == '[') {
            statement.push_back(Token(LSQR));
            this->advance();
        }
		else if (current_char == ']') {
			statement.push_back(Token(RSQR));
            this->advance();
		}
        else if (current_char == '*') {
            statement.push_back(Token(ASTER));
            this->advance();
        }
		else {
            string chr; 
            chr += "'"; 
            chr += this->current_char; 
            chr += "'";
			CharError err(chr, this->line, this->idx);
            err.RaiseErr(this->cmd);
		}
    }
    toks.push_back(statement);

    return true;
}

Token Lexer::make_number() {
    string num_str;
    bool is_float = false;
    while (is_in(this->current_char, DIGITS + '.')) {
        num_str += this->current_char;
        if (this->current_char == '.') {
            if (is_float) break;
            is_float = true;
        }
        this->advance();
    }

    if (num_str[-1] == '.') num_str += "0";
    else if (num_str[0] == '.') num_str.insert(0, "0");

    if (is_float) return Token(FLOAT, num_str);
    else return Token(INT, num_str);
}

Token Lexer::make_keyw() {
    string keyw;
    int pos_start = this->idx;
    while (!is_in<char, vector<char>>(this->current_char, WSPACE)) {
        if (is_in(this->current_char, ALPHA)) {
            keyw += this->current_char;
            this->advance();
        }
        else {
            string chr; 
            chr += "'"; 
            chr += this->current_char; 
            chr += "'";
            cout << int(this->current_char) << endl;
            CharError err(chr, this->line, this->idx);
            err.RaiseErr(this->cmd);
        }
    }

    if (!is_in<string, vector<string>>(keyw, KEYWS)) {
        KeywordError err("'" + keyw + "'", this->line, this->idx);
        err.RaiseErr(this->cmd, pos_start);
    }

    return Token(KEYW, keyw);
}