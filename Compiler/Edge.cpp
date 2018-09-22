//
// Created by Lenovo on 3/18/2018.
//

#include "Edge.h"
Edge::Edge(string val){
    value = val;
}
void Edge::toNode(Node *node) {
    to = node;
}
Node *Edge::getToNode(){
    return to;
}
string Edge::getValue(){
    return value;
}