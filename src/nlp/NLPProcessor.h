#ifndef NLP_PROCESSOR_H
#define NLP_PROCESSOR_H

#include <string>

using namespace std;


class NLPProcessor{
    public:
        string convertToDSL(const string& input);
};

#endif