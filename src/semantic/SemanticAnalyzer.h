#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "../parser/AST.h"
#include <unordered_map>
#include <string>

using namespace std;
class SemanticAnalyzer {
    unordered_map<string, bool> inputVars;
    unordered_map<string, pair<int,int>> ranges;
    bool otherwiseSeen;


    public:
        SemanticAnalyzer();
        void analyze(ASTNode* root);

    private:
        void visit(ASTNode* node);
        void handleInput(ASTNode* node);
        void handleRange(ASTNode* node);
        void handleIf(ASTNode* node);
        void handleOtherwise(ASTNode* node);
};



#endif