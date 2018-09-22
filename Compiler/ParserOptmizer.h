//
// Created by user on 4/20/2018.
//

#ifndef PARSERTREE_PARSEROPTMIZER_H
#define PARSERTREE_PARSEROPTMIZER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include<algorithm>
#include<iterator>
#include "StringVectorUtilis.h"
#define EPS "\\L"

using namespace StringVectorUtilis;
using namespace std;

class ParserOptmizer {
public:
    ParserOptmizer(map<string, vector<vector<string>>> parsGrammar, set<string> prodSet);
    map<string, vector<vector<string>>> finalGrammar;
    set<string> prodSet;

private:
    set<string> vis;
    map<string, vector<vector<string>>> grammarRec;
    void elimnateLeftFactor();
    void elimnateLeftRecursion(map<string, vector<vector<string>>> parsGrammar);
    vector<vector<string>> elimnateImmediateRecursion(vector<vector<string>> vec, string prod);
    void conctainateLeftFactor(map<string, vector<int>> mpIdx, vector<vector<string>> vec, string nonTerm);
    void createProdLeft(string prod, vector<int> idx, vector<vector<string>> vec);
    void createProdRec(string prod, vector<int> idx, vector<vector<string>> vec);
    void removeLeftFactor(string g, vector<vector<string>> v);
    vector<vector<string>> removeLeftRecursion(map<string, vector<vector<string>>> parsGrammar, string start);
    string createNewProdName(string s1, string s2, string s3);
};


#endif //PARSERTREE_PARSEROPTMIZER_H
