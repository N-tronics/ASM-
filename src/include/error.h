#ifndef ERROR_H
#define ERROR_H

#include <iostream>
using namespace std;

#define CHAR_ERROR				"Char Error"
#define KEYW_ERROR				"Keyword Error"
#define STACK_FULL				"Stack Full"
#define STACK_EMPTY				"Stack Empty"
#define LOAD_ERROR				"Load Error"
#define SYNTAX_ERROR			"Syntax Error"
#define DECIMAL_POINT_ERROR		"Decimal Point"

class Error {
public:
	string type; 
	string details;
	int line;
	int char_no;
	Error(string type_, string details_, int line_, int char_no_='\0') {
		this->type = type_;
		this->details = details_;
		this->line = line_;
		this->char_no = char_no_;
	}

	void RaiseErr(string cmd, int pos_start='\0');
};

class CharError : public Error {
public:
	CharError(string details_, int line_, int char_no_):Error(CHAR_ERROR, details_, line_, char_no_) {}
};

class KeywordError : public Error {
public:
	KeywordError(string details_, int line_, int char_no_):Error(KEYW_ERROR, details_, line_, char_no_) {}
};

class StackFullError : public Error {
public:
	StackFullError(string details_, int line_):Error(STACK_FULL, details_, line_) {}
};

class StackEmptyError : public Error {
public:
	StackEmptyError(string details_, int line_):Error(STACK_EMPTY, details_, line_) {}
};

class LoadError : public Error {
public:
	LoadError(string details_, int line_):Error(LOAD_ERROR, details_, line_) {}
};

class SyntaxError : public Error {
public:
	SyntaxError(string details_, int line_, int char_no_):Error(SYNTAX_ERROR, details_, line_, char_no_) {}
};

class DecimalPoint : public Error {
public:
	DecimalPoint(string details_, int line_, int char_no_):Error(DECIMAL_POINT_ERROR, details_, line_, char_no_) {}
};

void draw_pointer(string cmd, int pos);
void draw_underline(string cmd, int pos_start, int len);
string str_mul(char c, int i);

#endif