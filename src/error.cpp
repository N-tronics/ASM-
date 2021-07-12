#include <iostream>
#include "include/error.h"
using namespace std;

string str_mul(char c, int i) {
    string rslt;
    for (int _ = 0; _ < i; _++) rslt += c;

    return rslt;
}

void Error::RaiseErr(string cmd, int pos_start)  {
    if (this->type == STACK_FULL || this->type == STACK_EMPTY)
        cout << "Traceback: (" << this->line << ")" << endl;
    else
        cout << "Traceback: (" << this->line << ":" << this->char_no + 1 << ")" << endl;

    if (this->type == CHAR_ERROR)
        draw_pointer(cmd, this->char_no);
    else if (this->type == KEYW_ERROR)
        draw_underline(cmd, pos_start, this->char_no);
    else if (this->type == STACK_EMPTY || this->type == STACK_FULL)
        cout << cmd << endl;

    cout << this->type << ": " << this->details << "" << endl;
    exit(1);
}

void draw_pointer(string cmd, int pos) {
    cout << cmd << endl;
    cout << str_mul(' ', pos) << "^" << endl;
}

void draw_underline(string cmd, int pos_start, int len) {
    cout << cmd << endl;
    cout << str_mul(' ', pos_start) << str_mul('^', len + 1) << endl;
}