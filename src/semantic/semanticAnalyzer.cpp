#include "SemanticAnalyzer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

SemanticAnalyzer::SemanticAnalyzer() : otherwiseSeen(false){}

void SemanticAnalyzer::analyze(ASTNode* root){
    visit(root);
    cout<<" Semantic analysis Succesfull." <<endl;
}

void SemanticAnalyzer::visit(ASTNode* node){
    if(!node) return;

    if(node->nodeType == "Input"){
        handleInput(node);
    }else if(node->nodeType == "RangeRule"){
        handleRange(node);
    }else if(node->nodeType == "IfRule"){
        handleIf(node);
    }else if(node->nodeType == "OtherwiseRule"){
        handleOtherwise(node);
    }

    for( auto child : node->children){
        visit(child);
    }


}

void SemanticAnalyzer::handleInput(ASTNode* node){
    for(auto varNode: node->children[0]->children){
        inputVars[varNode->value] = true;
    }
}

void SemanticAnalyzer::handleRange(ASTNode* node){
    string var= node->children[0]->value;
    int min =  stoi(node->children[1]->value);
    int max = stoi(node->children[2]->value);
    if(!inputVars[var]){
        cerr <<"Semantic error: variable '"<<var
            << "' node declared in input" <<endl;
        exit(1);
    }

    if(ranges.count(var)){
        cerr<<"Semantic error: duplicate range for variable '"
            <<var <<"'"<<endl;
        exit(1);
    }

    ranges[var]= {min,max};

}

void SemanticAnalyzer::handleIf(ASTNode* node) {
    string var = node->children[1]->children[0]->value;
    int value = stoi(node->children[1]->children[2]->value);

    if (!ranges.count(var)) {
        cerr << "Semantic error: variable '" << var
             << "' used before range declaration" << endl;
        exit(1);
    }

    auto [min, max] = ranges[var];
    if (value < min || value > max) {
        cerr << "Semantic error: value out of range for variable '"
             << var << "'" << endl;
        exit(1);
    }
}

void SemanticAnalyzer::handleOtherwise(ASTNode* node) {
    if (otherwiseSeen) {
        cerr << "Semantic error: multiple 'otherwise' rules" << endl;
        exit(1);
    }
    otherwiseSeen = true;
}