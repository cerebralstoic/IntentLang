#include "IRGenerator.h"
#include <iostream>

using namespace std;

IRGenerator::IRGenerator() : labelCount(0), tempCount(0) {}

string IRGenerator::newLabel() {
    return "L" + to_string(labelCount++);
}

string IRGenerator::newTemp() {
    return "t" + to_string(tempCount++);
}

void IRGenerator::emit(string op, string arg1, string arg2, string result) {
    code.push_back(TAC(op, arg1, arg2, result));
}

void IRGenerator::generate(ASTNode* root) {
    visit(root);
}

void IRGenerator::visit(ASTNode* node) {
    if (!node) return;

    if (node->nodeType == "IfRule") {

        ASTNode* condition = node->children[1];

        string var = condition->children[0]->value;
        string op  = condition->children[1]->value;
        string val = condition->children[2]->value;

        string labelTrue = newLabel();

        emit("if", var + " " + op + " " + val, "", labelTrue);
    }

    if (node->nodeType == "OtherwiseRule") {

        string label = newLabel();
        emit("goto", "", "", label);
    }

    for (auto child : node->children)
        visit(child);
}

void IRGenerator::print() {

    cout << "\nIntermediate Code:\n";

    for (auto &t : code) {

        if (t.op == "if")
            cout << "if " << t.arg1
                 << " goto " << t.result << endl;

        else if (t.op == "goto")
            cout << "goto " << t.result << endl;

        else if (t.op == "label")
            cout << t.result << ":" << endl;

        else
            cout << t.result << " = "
                 << t.arg1 << " "
                 << t.op   << " "
                 << t.arg2 << endl;
    }
}