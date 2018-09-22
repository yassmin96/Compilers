//
// Created by Nada_Ayman on 3/15/2018.
//

#ifndef COMPILER_LANGUAGEPARSER_H
#define COMPILER_LANGUAGEPARSER_H

#include <string>
#include <stack>
#include <vector>
#include <map>
#include <cstring>
#include <iostream>
#include <regex>
#include "ParsingUtils.h"

using namespace std;
using namespace ParsingUtils;

class LexicalParser {

private:
    regex *keyword, *punctuation;
    map<string, vector<string> > lang, regs;
    map<string, string> basic;
    vector<string> lines;
    void initializeRegex();
    void addRegex(string key, string val);
    void separate(string &value);
    void putOperator(stack<string> & S, vector<string> &v, string str);
    void checkSubstitution(string &s);
    vector<string> getPostfix(vector<string> infix);
    bool isRegex(string s);
    bool isOperator(const string s);
    int hasHigherPrecedence(string op1, string op2);
    int getWeight(const string op);
    void Parse();

public:
    LexicalParser(vector<string> l);
    map<string, vector <string>> post;
    map<string, int> priority;
    vector<string> reserved, punc;
};

#endif //COMPILER_LANGUAGEPARSER_H
