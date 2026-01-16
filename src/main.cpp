#include <iostream>
#include "lexer/Lexer.cpp"

using namespace std;

int main() {
    Lexer lexer("../samples/marks.intent");

    Token token;
    do {
        token = lexer.getNextToken();
        cout << "TOKEN: " << (int)token.type 
             << " | LEXEME: [" << token.lexeme << "]"
             << " | LINE: " << token.line << endl;
    } while (token.type != TokenType::EOF_TOKEN);

    return 0;
}
