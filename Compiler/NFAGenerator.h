//
// Created by Dalia on 16/03/2018.
//

#ifndef UNTITLED_NFAGENERATOR_H
#define UNTITLED_NFAGENERATOR_H
#include<vector>
#include <iostream>
#include <string>
#include <map>
#include "Node.h"
#include "GraphGenerator.h"
#include <set>

using namespace std;

class NFAGenerator {
public:
    NFAGenerator();
    Node *startNode;
    void generateNFA(map<string, vector <string>> post, vector<string> reserved, vector<string> punc);
    void createKeywordNFA(vector<string> keywords);
    void createPuncNFA(vector<string> punc);
    void print(Node *src, set<Node*> nodeSet, set<Edge*> edgSet);
    void print();

private:
    void createKeywordOrPuncNFA(vector<string> keywords);
    void mergeWthStart(Node *node);
    GraphGenerator *graphGenerator;
    void createLanguageNFA(vector<string> grammer, string tokenType);
    Graph *evaluatePsitfixToGraph(vector<string> grammer);
    bool isOperator(string s);
};

#endif //UNTITLED_NFAGENERATOR_H
