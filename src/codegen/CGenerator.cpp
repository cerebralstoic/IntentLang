#include "CGenerator.h"
#include <fstream>

using namespace std;

void CGenerator::generate(ASTNode* root) {
    lines.push_back("#include <stdio.h>");
    lines.push_back("#include <string.h>");
    lines.push_back("");
    lines.push_back("int main() {");
    lines.push_back("    int marks;");
    lines.push_back("    char result[10];");
    lines.push_back("    scanf(\"%d\", &marks);");
    visit(root);
    lines.push_back("    printf(\"%s\", result);");
    lines.push_back("    return 0;");
    lines.push_back("}");
}

void CGenerator::visit(ASTNode* node) {
    if (!node) return;

    if (node->nodeType == "IfRule") {
        string var = node->children[1]->children[0]->value;
        string op  = node->children[1]->children[1]->value;
        string val = node->children[1]->children[2]->value;
        string res = node->children[0]->children.size() > 1
                     ? node->children[0]->children[1]->value
                     : node->children[0]->children[0]->value;

        if (lines.back().find("if") == string::npos)
            lines.push_back("    if (" + var + " " + op + " " + val + ") strcpy(result, \"" + res + "\");");
        else
            lines.push_back("    else if (" + var + " " + op + " " + val + ") strcpy(result, \"" + res + "\");");
    }

    if (node->nodeType == "OtherwiseRule") {
        string res = node->children[0]->children.size() > 1
                     ? node->children[0]->children[1]->value
                     : node->children[0]->children[0]->value;

        lines.push_back("    else strcpy(result, \"" + res + "\");");
    }

    for (auto child : node->children)
        visit(child);
}

void CGenerator::writeToFile(const string& filename) {
    ofstream out(filename);
    for (auto& line : lines)
        out << line << endl;
}
