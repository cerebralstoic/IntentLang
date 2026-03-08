#ifndef IR_GENERATOR_H
#define IR_GENERATOR_H

#include "../parser/AST.H"
#include "IR.h"
#include <vector>
#include <string>

using namespace std;
class IRGenerator{
    vector<TAC> code;
    int labelCount;
    int tempCount;
    public:
        IRGenerator();
        void generate(ASTNode* root);
        void print();
    private:
        void visit(ASTNode*  node);
        string newLabel();
        string newTemp();

        void emit(string op,
              string arg1 = "",
              string arg2 = "",
              string result = "");
};

#endif