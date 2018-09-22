//
// Created by Lenovo on 4/18/2018.
//

#ifndef COMPILER_SYNTAXPARSER_H
#define COMPILER_SYNTAXPARSER_H

#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <iostream>
#include <regex>
#include <set>
#include "ParsingUtils.h"

using namespace std;
using namespace ParsingUtils;

class SyntaxParser {

private:
    vector<string> lines;
    void Parse();

public:
    SyntaxParser(vector<string> l);
    map<string, vector<vector<string> > > productions;
    string start = "";
    set<string> getNonTerminals();
};


#endif //COMPILER_SYNTAXPARSER_H
