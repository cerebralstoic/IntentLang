#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

using namespace std;

struct ASTNode {
    string nodeType;
    string value;
    vector<ASTNode*> children;

    ASTNode(const string &type, const string & val = "")
        : nodeType(type), value(val){}
};

#endif