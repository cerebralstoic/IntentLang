#ifndef C_GENERATOR_H
#define C_GENERATOR_H

#include "../parser/AST.h"
#include <string>
#include <vector>

class CGenerator {
    std::vector<std::string> lines;

public:
    void generate(ASTNode* root);
    void writeToFile(const std::string& filename);

private:
    void visit(ASTNode* node);
};

#endif
