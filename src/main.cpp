#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "semantic/SemanticAnalyzer.h"
#include "ir/IRGenerator.h"
#include "codegen/CGenerator.h"
#include <iostream>

int main() {
    Lexer lexer("../samples/marks.intent");
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
