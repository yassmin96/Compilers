//
// Created by Lenovo on 3/18/2018.
//

#ifndef COMPILER_EDGE_H
#define COMPILER_EDGE_H



#include <iostream>
#include <string>
using namespace std;

class Node;

class Edge {

private:
    Node *to;
    string value;
	
public:
    Edge(string val);
    void toNode(Node *node);
    Node* getToNode();
    string getValue();
};


#endif //COMPILER_EDGE_H
