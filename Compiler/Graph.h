//
// Created by Lenovo on 3/18/2018.
//

#ifndef COMPILER_GRAPH_H
#define COMPILER_GRAPH_H
#include<vector>
#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class Graph{
public:
    Graph(Node *node1, Node *node2);
    Node *getInitialNode();
    Node *getFinalNode();
private:
    Node *initial;
    Node *final;
};
#endif //COMPILER_GRAPH_H
