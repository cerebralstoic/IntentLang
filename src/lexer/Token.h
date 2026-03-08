#ifndef TOKEN_H
#define TOKEN_H
#include <string>


enum class TokenType {
    GOAL, INPUT, CONSTRAINTS, OUTPUT,
    RANGE, TO , IF , OTHERWISE,
    INT_TYPE,
    FLOAT_TYPE,
    STRING_TYPE,
    BOOL_TYPE,
    IDENTIFIER, NUMBER,
    COLON, COMMA,
    REL_OP,
    EOF_TOKEN
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

#endif