#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include <iostream>

int main() {
    Lexer lexer("../samples/marks.intent");
    Parser parser(lexer);

    ASTNode* ast = parser.parseProgram();
    std::cout << "Parsing successful.\n";

    return 0;
}
