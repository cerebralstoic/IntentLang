#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <fstream>
#include <string>

class Lexer {
    std::ifstream file;
    int currentChar;
    int line;

public:
    Lexer(const std::string& filename);
    Token getNextToken();

private:
    Token keywordOrIdentifier(const std::string& word);
};

#endif
