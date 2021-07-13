#include "include/cpu.h"
#include "include/error.h"
#include "include/lexer.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/////////////////////////////////////////////////////////
// CPU
/////////////////////////////////////////////////////////

void CPU::set_cmds(string cmd_, string statement_) {
	this->cmd = cmd_;
	this->statement = statement_;
}

void CPU::update_line(int line_) {
	this->line = line_;
}

void CPU::lda(int val_) {
	this->a_register = val_;
}

void CPU::ldb(int val_) {
	this->b_register = val_;
}

void CPU::ldc(int val_) {
	this->c_register = val_;
}

void CPU::lds(int val_) {
	this->support_register = val_;
}

void CPU::ldo(int val_) {
	this->output_register = val_;
}

void CPU::inc(string val_) {
	if (val_ == "areg") {
		this->a_register++;
	}
	else if (val_ == "breg") {
		this->b_register++;
	}
	else if (val_ == "creg") {
		this->c_register++;
	}
	else if (val_ == "sreg") {
		this->support_register++;
	}
	else if (val_ == "oreg") {
		this->output_register++;
	}
}

void CPU::dec(string val_) {
	if (val_ == "areg") {
		this->a_register--;
	}
	else if (val_ == "breg") {
		this->b_register--;
	}
	else if (val_ == "creg") {
		this->c_register--;
	}
	else if (val_ == "sreg") {
		this->support_register--;
	}
	else if (val_ == "oreg") {
		this->output_register--;
	}
}

void CPU::push(int val_) {
	if (this->stack.size() < CPU_STACK_SIZE) {
		this->stack.push_back(val_);
	} else {
		StackFullError err(this->cmd, this->line);
		err.RaiseErr(this->statement);
	}
}

void CPU::pull() {
	if (!this->stack.empty()) {
		this->lds(this->stack[this->stack.size() - 1]);
		this->stack.pop_back();
	} else {
		StackEmptyError err(this->cmd, this->line + 1);
		err.RaiseErr(this->statement);
	}
}

void CPU::sum() {
	this->lds(this->a_register + this->b_register);
}

void CPU::out() {
	cout << this->output_register << endl;
}

/////////////////////////////////////////////////////////
// Interpreter
/////////////////////////////////////////////////////////

Interpreter::Interpreter(vector<vector<Token>> toks_) {
	this->toks = toks_;
	this->execute();
}

void Interpreter::execute() {
	for (int i = 0; i < this->toks.size(); i++) {
		this->cpu.update_line(i);
		this->line = i;
		Token cmd = this->toks[i][0];
		if (this->toks[i].size() == 2) {
			Token value = this->toks[i][1];

			int val;
			if (value.value == "areg") 
				val = this->cpu.BREG();
			else if (value.value == "breg")
				val = this->cpu.BREG();
			else if (value.value == "creg")
				val = this->cpu.CREG();
			else if (value.value == "sreg")
				val = this->cpu.SREG();
			else if (value.value == "oreg")
				val = this->cpu.OREG();

			if (cmd.value == "lda") {
				if (value.type == INT)
					this->cpu.lda(stoi(value.value));
				else if (value.type == KEYW) {
					if (value.value == "areg") {
						LoadError err(value.value, this->line + 1);
						err.RaiseErr(cmd.value + " " + value.value);
					}
					else
						this->cpu.lda(val);
				}
			}
			else if (cmd.value == "ldb") {
				if (value.type == INT)
					this->cpu.ldb(stoi(value.value));
				else if (value.type == KEYW) {
					if (value.value == "breg") {
						LoadError err(value.value, this->line + 1);
						err.RaiseErr(cmd.value + " " + value.value);
					}
					else
						this->cpu.ldb(val);
				}
			}
			else if (cmd.value == "ldc") {
				if (value.type == INT)
					this->cpu.ldc(stoi(value.value));
				else if (value.type == KEYW) {
					if (value.value == "creg") {
						LoadError err(value.value, this->line + 1);
						err.RaiseErr(cmd.value + " " + value.value);
					}
					else
						this->cpu.ldc(val);
				}
			}
			else if (cmd.value == "lds") {
				if (value.type == INT)
					this->cpu.lds(stoi(value.value));
				else if (value.type == KEYW) {
					if (value.value == "sreg") {
						LoadError err(value.value, this->line + 1);
						err.RaiseErr(cmd.value + " " + value.value);
					}
					else
						this->cpu.lds(val);
				}
			}
			else if (cmd.value == "ldo") {
				if (value.type == INT)
					this->cpu.ldo(stoi(value.value));
				else if (value.type == KEYW) {
					if (value.value == "oreg") {
						LoadError err(value.value, this->line + 1);
						err.RaiseErr(cmd.value + " " + value.value);
					}
					else
						this->cpu.ldo(val);
				}
			}
			else if (cmd.value == "push") {
				if (value.type == INT)
					this->cpu.push(stoi(value.value));
				else if (value.type == KEYW)
					this->cpu.push(val);
			}
			else if (cmd.value == "inc") {
				if (value.type == KEYW)
					this->cpu.inc(value.value);
			}
			else if (cmd.value == "dec") {
				if (value.type == KEYW)
					this->cpu.dec(value.value);
			}
		} 
		else {
			if (cmd.value == "pull") this->cpu.pull();
			else if (cmd.value == "sum") this->cpu.sum();
			else if (cmd.value == "out") this->cpu.out();
			else continue;
		}
	}
}