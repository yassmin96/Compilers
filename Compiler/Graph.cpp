//
// Created by Lenovo on 3/18/2018.
//

#include "Graph.h"

Graph::Graph(Node *node1, Node *node2){
    initial = node1;
    final = node2;
}

Node *Graph::getInitialNode(){
    return initial;
}

Node *Graph::getFinalNode(){
    return final;
}