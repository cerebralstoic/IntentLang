#ifndef IR_GENERATOR_H
#define IR_GENERATOR_

#include "../parser/AST.H"
#include "IR.h"
#include <vector>

using namespace std;
class IRGenerator{
    vector<TAC> code;
    int labelCount;
    public:
        IRGenerator();
        void generate(ASTNode* root);
        void print();
    private:
        void visit(ASTNode*  node);
        string newLabel();
};

#endif