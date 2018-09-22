//
// Created by Dalia on 16/03/2018.
//

#ifndef UNTITLED_GRAPHGENERATOR_H
#define UNTITLED_GRAPHGENERATOR_H

#include<vector>
#include <iostream>
#include <string>
#include "Node.h"
#include "Graph.h"
#include <set>
#include <queue>
using namespace std;

class GraphGenerator {
	
public:
    GraphGenerator();
    Graph *genGraphKeyword(string keyword);
    Graph *genLexemGraph(string token);
    Graph *connectORgraph(Graph *one, Graph *two);
    Graph *connectANDgraph(Graph *one, Graph *two);
    Graph *connectASTRkgraph(Graph *one);
    Graph *connectPLUSgraph(Graph *one);
    void connectEdgeWithNodes(Node *one, Edge *edg, Node *two);
    Graph *genGraphPunc(string punc);
	
private:
    vector<Edge*> getEdgesOfFour();
    void connectBottleneck(Edge *edg, Node *node);
    Graph *getCopyGraph(Graph *grph);
    int counter;

};
#endif //UNTITLED_GRAPHGENERATOR_H
