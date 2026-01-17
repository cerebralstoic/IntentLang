#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "semantic/SemanticAnalyzer.h"
#include <iostream>

int main() {
    Lexer lexer("../samples/marks.intent");
    Parser parser(lexer);

    ASTNode* ast = parser.parseProgram();
    std::cout << "Parsing successful." << std::endl;

    SemanticAnalyzer sem;
    sem.analyze(ast);

    return 0;
}
