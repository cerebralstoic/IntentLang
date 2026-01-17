#include "IRGenerator.h"
#include <iostream>

using namespace std;

IRGenerator::IRGenerator() : labelCount(0){}

string IRGenerator::newLabel(){
    return "L"+ to_string(labelCount++);
}

void IRGenerator::generate(ASTNode* root) {
    visit(root);
}

void IRGenerator::visit(ASTNode* node) {
    if (!node) return;

    if (node->nodeType == "IfRule") {
        string label = newLabel();
        TAC t;
        t.op = "if";
        t.arg1 = node->children[1]->children[0]->value;
        t.arg2 = node->children[1]->children[2]->value;
        t.result = label;
        code.push_back(t);
    }

    if (node->nodeType == "OtherwiseRule") {
        TAC t;
        t.op = "goto";
        t.result = newLabel();
        code.push_back(t);
    }

    for (auto child : node->children)
        visit(child);
}

void IRGenerator::print() {
    cout << "\nIntermediate Code:\n";
    for (auto& t : code) {
        if (t.op == "if")
            cout << "if " << t.arg1 << " ? " << t.arg2
                 << " goto " << t.result << endl;
        else
            cout << "goto " << t.result << endl;
    }
}