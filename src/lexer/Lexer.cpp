#include "Token.h"
#include <fstream>
#include <cctype>
#include <unordered_map>
#include<iostream>
using namespace std;

class Lexer{
    ifstream file;
    char currentChar;
    int line;
    public:
        Lexer(const string & filename) :line(1){
            file.open(filename);
            if (!file.is_open()) {
                 cout<< "ERROR: Cannot open file!"<<endl;
            exit(1);
            }
            currentChar = file.get();
        }

        Token getNextToken(){
            while(isspace(currentChar)){
                if(currentChar == '\n'){
                    line ++;
                }
                currentChar =file.get();
            }

            if(file.eof()){
                return {TokenType::EOF_TOKEN,"",line};
            }

            if(isalpha(currentChar)){
                string word;
                while(isalnum(currentChar) || currentChar == '_'){
                    word+= currentChar;
                    currentChar = file.get();
                }
                return keywordOrIdentifier(word);
            }

            if(isdigit(currentChar)){
                string num;
                while(isdigit(currentChar)){
                    num+=currentChar;
                    currentChar= file.get();
                }

                return {TokenType::NUMBER,num,line};
            }

            if(currentChar == ':'){
                currentChar = file.get();
                return {TokenType::COLON,":",line};
            }

            if(currentChar == ','){
                currentChar = file.get();
                return {TokenType::COMMA,",",line};
            }

            if(currentChar == '<' || currentChar == '>'){
                string op;
                op +=currentChar;

                currentChar = file.get();

                if(currentChar == '='){
                    op += currentChar;
                    currentChar = file.get();
                }

                return {TokenType::REL_OP,op,line};
            }

            currentChar = file.get();
            return getNextToken();

        }

        private:
            Token keywordOrIdentifier(const string & word){
                static unordered_map<string, TokenType> keywords ={
                    {"goal",TokenType::GOAL},
                    {"input",TokenType::INPUT},
                    {"constraints",TokenType::CONSTRAINTS},
                    {"output",TokenType::OUTPUT},
                    {"range",TokenType::RANGE},
                    {"to",TokenType::TO},
                    {"if",TokenType::IF},      
                    {"otherwise",TokenType::OTHERWISE}             
                };

                if(keywords.count(word))
                    return {keywords[word],word,line};

                return {TokenType::IDENTIFIER,word,line};
            }

};
