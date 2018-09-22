//
// Created by Dalia on 16/03/2018.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H


#include<vector>
#include <iostream>
#include <string>
#include "Edge.h"

using namespace std;


class Node {

private:
    vector<Edge*>  out, in;
    Node *copy;
    bool final;
    string tokenType;
    int nodeCount;
	
public:
    Node(int count);
    string name;
    void addToOutlist(Edge *edge);
    void setFinal(string type);
    vector<Edge*> getEdgeOutList();
    void setCopy(Node *node);
    Node *getCopy();
    string getFinalType();
    bool isFinal();
    int getNodeCount();
};
#endif //UNTITLED_NODE_H
