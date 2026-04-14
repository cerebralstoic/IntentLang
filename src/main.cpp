#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "semantic/SemanticAnalyzer.h"
#include "ir/IRGenerator.h"
#include "codegen/CGenerator.h"
#include <iostream>
#include "nlp/NLPProcessor.h"
#include <fstream>

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

    ofstream out("../samples/generated.intent");

    out << "goal: test\n\n";
    out << "input:\n    int marks\n\n";

    out << "constraints:\n";
    bool hasRange = false;

    for (auto &rule : dslRules) {
        if (rule.find("range") != string::npos)
            hasRange = true;
    }
    
    if (!hasRange) {
        out << "    marks range 0 to 100\n";
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

    std::cout << "Parsing successful.\n";

    SemanticAnalyzer sem;
    sem.analyze(ast);

    IRGenerator ir;
    ir.generate(ast);
    ir.print();

    CGenerator gen;
    gen.generate(ast);
    gen.writeToFile("output.c");

    std::cout << "\nC code generated: output.c\n";
    return 0;
}
