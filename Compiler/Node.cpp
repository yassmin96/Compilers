//
// Created by Dalia on 16/03/2018.
//

#include "Node.h"
Node::Node(int count){
    nodeCount = count;
    final = false;
}
void Node::addToOutlist(Edge *edge){
    out.push_back(edge);
}
void Node::setFinal(string type){
    final = true;
    tokenType = type;
}
void Node::setCopy(Node *node){
    copy = node;
}
Node *Node::getCopy(){
    return copy;
}
vector<Edge*> Node::getEdgeOutList(){
    return out;
}
string Node::getFinalType(){
    return tokenType;
}
bool Node::isFinal(){
    return final;
}
int  Node::getNodeCount(){
    return nodeCount;
}
