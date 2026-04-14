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
    string input;
    cout<<"Enter rule in natural language:";
    getline(cin, input);

    string dslRule = nlp.convertToDSL(input);

    ofstream out("../samples/generated.intent");

    out << "goal: test\n\n";
    out << "input:\n    int marks\n\n";
    out << "constraints:\n";
    out << "    marks range 0 to 100\n";
    out << "    " << dslRule << "\n\n";
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
