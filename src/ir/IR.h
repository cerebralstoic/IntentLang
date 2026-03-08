#ifndef IR_H
#define IR_H

#include <string>
#include <vector>

using namespace std;

struct TAC{
    string op;
    string arg1;
    string arg2;
    string result;

    TAC(string o, string a1="", string a2="", string r="")
        : op(o), arg1(a1), arg2(a2), result(r) {}
};


#endif