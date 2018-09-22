//
// Created by Lenovo on 3/15/2018.
//

#ifndef COMPILER_DFAGENERATOR_H
#define COMPILER_DFAGENERATOR_H


#include "Node.h"
#include <vector>
#include <string>
#include <stack>
#include <regex>
#include <iostream>
#include <algorithm>
#include "Edge.h"
#include "TokenPath.h"
#include "LexicalParser.h"
#include "ParserTreeGenerator.h"

using namespace std;

class DFAGenerator
{

public:
    DFAGenerator(Node* s,LexicalParser *lngParser, ParserTreeGenerator *pt);
    TableRow* Eclosure(TableRow *row);
    void tableGenerator();
    void Minimize();
    int countSame(vector<Node*> one, vector<Node*> two);
    void getOutL(Node* s);
    void findToken(vector <string> s);

private:
    vector<TableRow*> states;
    LexicalParser *lp;
    vector<TableRow*> toNodes ;
    vector<TokenPath*> tokPath;
    void adder (TokenPath *newPath ,TableRow* iterSecond, int i);
    ParserTreeGenerator *parserTree;

};


#endif //COMPILER_DFAGENERATOR_H
