#include "Parser.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Parser::Parser(Lexer& lex) : lexer(lex) {
    currentToken = lexer.getNextToken();
    nextToken = lexer.getNextToken();
}

void Parser::advance() {
    currentToken = nextToken;
    nextToken = lexer.getNextToken();
}

void Parser::match(TokenType type) {
    if (currentToken.type == type) {
        advance();
    } else {
        cerr << "Syntax error at line "
             << currentToken.line
             << ", expected token "
             << static_cast<int>(type)
             << endl;
        exit(1);
    }
}

ASTNode* Parser::parseProgram() {
    ASTNode* root = new ASTNode("Program");
    root->children.push_back(parseGoal());
    root->children.push_back(parseInput());
    root->children.push_back(parseConstraints());
    root->children.push_back(parseOutput());
    return root;
}

ASTNode* Parser::parseGoal() {
    match(TokenType::GOAL);
    match(TokenType::COLON);
    ASTNode* node = new ASTNode("Goal", currentToken.lexeme);
    match(TokenType::IDENTIFIER);
    return node;
}

ASTNode* Parser::parseInput() {
    match(TokenType::INPUT);
    match(TokenType::COLON);
    ASTNode* node = new ASTNode("Input");
    node->children.push_back(parseVarList());
    return node;
}

ASTNode* Parser::parseVarList() {
    ASTNode* node = new ASTNode("VarList");
    node->children.push_back(new ASTNode("Var", currentToken.lexeme));
    match(TokenType::IDENTIFIER);
    if (currentToken.type == TokenType::COMMA) {
        match(TokenType::COMMA);
        node->children.push_back(parseVarList());
    }
    return node;
}

ASTNode* Parser::parseConstraints() {
    match(TokenType::CONSTRAINTS);
    match(TokenType::COLON);
    ASTNode* node = new ASTNode("Constraints");
    node->children.push_back(parseConstraintList());
    return node;
}

ASTNode* Parser::parseConstraintList() {
    ASTNode* node = new ASTNode("ConstraintList");
    while (currentToken.type != TokenType::OUTPUT &&
           currentToken.type != TokenType::EOF_TOKEN) {
        node->children.push_back(parseConstraint());
    }
    return node;
}

ASTNode* Parser::parseConstraint() {
    if (currentToken.type == TokenType::IDENTIFIER &&
        nextToken.type == TokenType::RANGE) {

        ASTNode* node = new ASTNode("RangeRule");

        node->children.push_back(
            new ASTNode("Var", currentToken.lexeme)
        );
        match(TokenType::IDENTIFIER);
        match(TokenType::RANGE);

        node->children.push_back(
            new ASTNode("Min", currentToken.lexeme)
        );
        match(TokenType::NUMBER);

        match(TokenType::TO);

        node->children.push_back(
            new ASTNode("Max", currentToken.lexeme)
        );
        match(TokenType::NUMBER);

        return node;
    }

    ASTNode* action = parseAction();

    if (currentToken.type == TokenType::IF) {
        ASTNode* node = new ASTNode("IfRule");
        node->children.push_back(action);
        match(TokenType::IF);
        node->children.push_back(parseCondition());
        return node;
    }

    if (currentToken.type == TokenType::OTHERWISE) {
        ASTNode* node = new ASTNode("OtherwiseRule");
        node->children.push_back(action);
        match(TokenType::OTHERWISE);
        return node;
    }

    cerr << "Syntax error at line "
         << currentToken.line
         << ", expected IF or OTHERWISE"
         << endl;
    exit(1);
}

ASTNode* Parser::parseAction() {
    ASTNode* node = new ASTNode("Action");
    node->children.push_back(
        new ASTNode("Name", currentToken.lexeme)
    );
    match(TokenType::IDENTIFIER);
    if (currentToken.type == TokenType::IDENTIFIER) {
        node->children.push_back(
            new ASTNode("Value", currentToken.lexeme)
        );
        match(TokenType::IDENTIFIER);
    }
    return node;
}

ASTNode* Parser::parseCondition() {
    ASTNode* node = new ASTNode("Condition");
    node->children.push_back(
        new ASTNode("Var", currentToken.lexeme)
    );
    match(TokenType::IDENTIFIER);
    node->children.push_back(
        new ASTNode("Op", currentToken.lexeme)
    );
    match(TokenType::REL_OP);
    node->children.push_back(
        new ASTNode("Value", currentToken.lexeme)
    );
    match(TokenType::NUMBER);
    return node;
}

ASTNode* Parser::parseOutput() {
    match(TokenType::OUTPUT);
    match(TokenType::COLON);
    ASTNode* node = new ASTNode("Output");
    node->children.push_back(parseVarList());
    return node;
}
