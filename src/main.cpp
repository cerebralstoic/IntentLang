#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "semantic/SemanticAnalyzer.h"
#include "ir/IRGenerator.h"
#include "codegen/CGenerator.h"
#include "nlp/NLPProcessor.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main() {

    NLPProcessor nlp;

    vector<string> inputs;
    string line;

    cout << "Enter rules (type END to finish):\n";

    while (true) {
        getline(cin, line);
        if (line == "END") break;
        if (!line.empty())
            inputs.push_back(line);
    }

    vector<string> dslRules;

    for (auto &inp : inputs) {
        string rule = nlp.convertToDSL(inp);
        cout << "DSL: " << rule << endl;
        dslRules.push_back(rule);
    }

    set<string> variables = nlp.extractVariables(dslRules);

    if (variables.empty()) {
        variables.insert("marks");
    }

    ofstream out("../samples/generated.intent");

    out << "goal: test\n\n";

    out << "input:\n";
    for (auto &var : variables) {
        out << "    int " << var << "\n";
    }
    out << "\n";

    out << "constraints:\n";

    for (auto &var : variables) {

        bool hasVarRange = false;

        for (auto &rule : dslRules) {
            if (rule.find(var + " range") != string::npos) {
                hasVarRange = true;
                break;
            }
        }

        if (!hasVarRange) {
            out << "    " << var << " range 0 to 100\n";
        }
    }

    for (auto &rule : dslRules) {
        out << "    " << rule << "\n";
    }

    out << "\n";
    out << "output:\n    grade\n";

    out.close();

    Lexer lexer("../samples/generated.intent");
    Parser parser(lexer);
    ASTNode* ast = parser.parseProgram();

    cout << "Parsing successful.\n";

    SemanticAnalyzer sem;
    sem.analyze(ast);

    IRGenerator ir;
    ir.generate(ast);
    ir.print();

    CGenerator gen;
    gen.generate(ast);
    gen.writeToFile("output.c");

    cout << "\nC code generated: output.c\n";

    return 0;
}