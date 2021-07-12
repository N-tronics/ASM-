#ifndef CPU_H
#define CPU_H

#include <vector>
#include "lexer.h"
using namespace std;

#define CPU_STACK_SIZE 32

class CPU {
private:
	vector<int> stack;
	int line = 0;
	int a_register = 0;
	int b_register = 0;
	int c_register = 0;
	int support_register = 0;
	int output_register = 0;
	string cmd;
	string statement;
public:
	CPU() {}
	int AREG() { return this->a_register; }
	int BREG() { return this->b_register; }
	int CREG() { return this->c_register; }
	int SREG() { return this->support_register; }
	int OREG() { return this->output_register; }
	void set_cmds(string cmd_, string statement_);
	void update_line(int line_);
	void lda(int val_);
	void ldb(int val_);
	void ldc(int val_);
	void lds(int val_);
	void ldo(int val_);
	void inc(string val_);
	void dec(string val_);
	void push(int val_);
	void pull();
	void sum();
	void out();
};

class Interpreter {
private:
	CPU cpu;
	vector<vector<Token>> toks;
public:
	int line = 0;
	Interpreter(vector<vector<Token>> toks_);
	void execute();
};

#endif