#ifndef PARSER_H
#define PARSER_H

#include "../lexer/Lexer.h"
#include "AST.H"

class Parser{
    Lexer & lexer;
    Token currentToken;
    Token nextToken;

    public:
        Parser(Lexer &lex);
        ASTNode* parseProgram();

    private:
        void advance();
        void match(TokenType type);

        ASTNode* parseGoal();
        ASTNode* parseInput();
        ASTNode* parseVarList();
        ASTNode* parseConstraints();
        ASTNode* parseConstraintList();
        ASTNode* parseConstraint();
        ASTNode* parseRangeRule();
        ASTNode* parseIfRule();
        ASTNode* parseOtherwiseRule();
        ASTNode* parseAction();
        ASTNode* parseCondition();
        ASTNode* parseOutput();
};


#endif