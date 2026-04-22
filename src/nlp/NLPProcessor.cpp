#include "NLPProcessor.h"
#include <algorithm>
#include <sstream>
#include <set>

using namespace std;
string NLPProcessor::convertToDSL(const string& input) {

    string s = input;

    transform(s.begin(), s.end(), s.begin(), ::tolower);
    if (s.find("otherwise") != string::npos && s.find("grade") != string::npos && s.find("assign") == string::npos) {
        return input;
    }
    if (s.find(" if ") != string::npos || s.find(" range    ") != string::npos) {
        return input;
    }

    if (s.find(" if ") != string::npos || 
        s.find(" range ") != string::npos) {
        return input;
    }

    if (s.find("between") != string::npos && s.find("and") != string::npos) {
        int a, b;
        sscanf(s.c_str(), "marks between %d and %d", &a, &b);
        return "marks range " + to_string(a) + " to " + to_string(b);
    }

    if (s.find("greater than or equal to") != string::npos)
        s.replace(s.find("greater than or equal to"), 27, ">=");

    if (s.find("greater than") != string::npos)
        s.replace(s.find("greater than"), 12, ">");

    if (s.find("less than") != string::npos)
        s.replace(s.find("less than"), 9, "<");

    if (s.find("otherwise") != string::npos) {

        if (s.find("assign grade") != string::npos)
            s.replace(s.find("assign grade"), 12, "grade");

        size_t pos = s.find("grade");

        if (pos != string::npos) {
            string action = s.substr(pos);

            if (action.size() > 6)
                action[6] = toupper(action[6]);

            return action + " otherwise";
        }
    }

    if (s.find("fail") != string::npos) {

        if (s.find("then") != string::npos)
            s.erase(s.find("then"), 4);

        if (s.find("if") != string::npos)
            s.erase(s.find("if"), 2);

        size_t pos = s.find("fail");
        string condition = s.substr(0, pos);

        return "fail if " + condition;
    }

    if (s.find("assign grade") != string::npos)
        s.replace(s.find("assign grade"), 12, "grade");

    if (s.find("then") != string::npos)
        s.erase(s.find("then"), 4);

    if (s.find("if") != string::npos)
        s.erase(s.find("if"), 2);

    size_t pos = s.find("grade");

    if (pos != string::npos) {
        string condition = s.substr(0, pos);
        string action = s.substr(pos);

        if (action.size() > 6)
            action[6] = toupper(action[6]);

        return action + " if " + condition;
    }

    return input;
}

set<string> NLPProcessor::extractVariables(const vector<string>& rules){

    set<string> vars;
    for(auto &rule: rules){
        stringstream ss(rule);
        string word;
        while(ss>> word){

            if(word == "if"){
                string var;
                ss>>var;
                vars.insert(var);
            }
            if(word == "range"){
                string var;
            }
        }
    }

    return vars;
}