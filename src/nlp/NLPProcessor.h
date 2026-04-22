#ifndef NLP_PROCESSOR_H
#define NLP_PROCESSOR_H

#include <string>
#include <set>
#include <vector>

using namespace std;


class NLPProcessor{
    public:
        string convertToDSL(const string& input);
        set<string> extractVariables(const vector<string>& rules);
};

#endif