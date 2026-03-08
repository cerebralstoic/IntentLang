#include "CGenerator.h"
#include <fstream>

using namespace std;

void CGenerator::generate(ASTNode* root) {

    lines.push_back("#include <stdio.h>");
    lines.push_back("#include <string.h>");
    lines.push_back("");
    lines.push_back("int main() {");

    generateInputs(root);
    generateOutputs(root);

    visit(root);

    lines.push_back("    printf(\"%s\\n\", " + outputVar + ");");
    lines.push_back("    return 0;");
    lines.push_back("}");
}

void CGenerator::generateInputs(ASTNode* root) {

    for (auto child : root->children) {

        if (child->nodeType == "Input") {

            for (auto varList : child->children) {

                for (auto varNode : varList->children) {

                    string name = varNode->value;
                    string type = varNode->dataType;

                    if (type == "int") {
                        lines.push_back("    int " + name + ";");
                        lines.push_back("    scanf(\"%d\", &" + name + ");");
                    }

                    else if (type == "float") {
                        lines.push_back("    float " + name + ";");
                        lines.push_back("    scanf(\"%f\", &" + name + ");");
                    }

                    else if (type == "bool") {
                        lines.push_back("    int " + name + ";");
                        lines.push_back("    scanf(\"%d\", &" + name + ");");
                    }

                    else if (type == "string") {
                        lines.push_back("    char " + name + "[100];");
                        lines.push_back("    scanf(\"%s\", " + name + ");");
                    }
                }
            }
        }
    }

    lines.push_back("");
}

void CGenerator::generateOutputs(ASTNode* root) {

    for (auto child : root->children) {

        if (child->nodeType == "Output") {

            string var = child->children[0]->children[0]->value;

            outputVar = var;

            lines.push_back("    char " + var + "[20];");
            lines.push_back("");
        }
    }
}

void CGenerator::visit(ASTNode* node) {

    if (!node) return;

    if (node->nodeType == "IfRule") {

        string var = node->children[1]->children[0]->value;
        string op  = node->children[1]->children[1]->value;
        string val = node->children[1]->children[2]->value;

        string res =
            node->children[0]->children.size() > 1
            ? node->children[0]->children[1]->value
            : node->children[0]->children[0]->value;

        if (lines.back().find("if") == string::npos)
            lines.push_back("    if (" + var + " " + op + " " + val + ") strcpy(" + outputVar + ", \"" + res + "\");");

        else
            lines.push_back("    else if (" + var + " " + op + " " + val + ") strcpy(" + outputVar + ", \"" + res + "\");");
    }

    if (node->nodeType == "OtherwiseRule") {

        string res =
            node->children[0]->children.size() > 1
            ? node->children[0]->children[1]->value
            : node->children[0]->children[0]->value;

        lines.push_back("    else strcpy(" + outputVar + ", \"" + res + "\");");
    }

    for (auto child : node->children)
        visit(child);
}

void CGenerator::writeToFile(const string& filename) {

    ofstream out(filename);

    for (auto &line : lines)
        out << line << endl;
}