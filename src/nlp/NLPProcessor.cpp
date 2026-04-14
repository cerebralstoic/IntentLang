#include "NLPProcessor.h"
#include <algorithm>

using namespace std;

string NLPProcessor::convertToDSL(const string& input) {

    string s = input;

    
    transform(s.begin(), s.end(), s.begin(), ::tolower);

    if (s.find("greater than or equal to") != string::npos)
        s.replace(s.find("greater than or equal to"), 27, ">=");

    if (s.find("greater than") != string::npos)
        s.replace(s.find("greater than"), 12, ">");

    if (s.find("less than") != string::npos)
        s.replace(s.find("less than"), 9, "<");

    if (s.find("assign grade") != string::npos)
        s.replace(s.find("assign grade"), 12, "grade");

    if (s.find("if") != string::npos)
        s.erase(s.find("if"), 2);

    if (s.find("then") != string::npos)
        s.erase(s.find("then"), 4);

    if (s.find("are") != string::npos)
        s.erase(s.find("are"), 3);

    size_t pos = s.find("grade");

    if (pos != string::npos) {
        string condition = s.substr(0, pos);
        string action = s.substr(pos);

        return action + " if " + condition;
    }

    return s;
}