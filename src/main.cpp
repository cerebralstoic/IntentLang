#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "semantic/SemanticAnalyzer.h"
#include "ir/IRGenerator.h"
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

    return 0;
}
