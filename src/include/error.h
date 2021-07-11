#ifndef ERROR_H
#define ERROR_H

#include <iostream>
using namespace std;

const string CHAR_ERROR			= "Char Error";
const string KEYW_ERROR			= "Keyword Error";

class Error {
public:
	string type; 
	string details;
	int line;
	int char_no;
	Error(string type_, string details_, int line_, int char_no_) {
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

void draw_pointer(string cmd, int pos);
void draw_underline(string cmd, int pos_start, int len);
string str_mul(char c, int i);

#endif