//
// Created by Dalia on 16/03/2018.
//

#include "GraphGenerator.h"
GraphGenerator::GraphGenerator(){
    counter = 1;
}
Graph *GraphGenerator::genGraphPunc(string punc){
    auto *start = new Node(counter++);
    auto *end = new Node(counter++);
    Edge *edge = new Edge(punc);
    connectEdgeWithNodes(start, edge, end);
    auto *g = new Graph(start, end);
    return g;
}
Graph *GraphGenerator::genGraphKeyword(string keyword) {
    auto *start = new Node(counter++);
    auto *from = start;
    Node *to = NULL;

    for (int i = 0; i < keyword.size(); i++) {
        to = new Node(counter++);
        Edge *edge = new Edge(string(1, keyword[i]));
        edge->toNode(to);
        from->addToOutlist(edge);
        from = to;
    }

    auto *g = new Graph(start, to);
    return g;
}
Graph *GraphGenerator::genLexemGraph(string token){
    Node *init = new Node(counter++);
    Node *fin = new Node(counter++);
    Edge *edg = new Edge(token);
    connectEdgeWithNodes(init, edg, fin);
    auto *g = new Graph(init, fin);
    return g;
}
Graph *GraphGenerator::connectORgraph(Graph *one, Graph *two){
    vector<Edge*> edges = getEdgesOfFour();
    auto *init = new Node(counter++);
    auto *fin = new Node(counter++);
    connectEdgeWithNodes(init, edges[0], one->getInitialNode());
    connectEdgeWithNodes(init, edges[1], two->getInitialNode());
    connectEdgeWithNodes(one->getFinalNode(), edges[2], fin);
    connectEdgeWithNodes(two->getFinalNode(), edges[3], fin);
    auto *g = new Graph(init, fin);
    return g;
}
Graph *GraphGenerator::connectANDgraph(Graph *one, Graph *two){
    vector<Edge*> outList = one->getInitialNode()->getEdgeOutList();
    for(int i = 0; i < outList.size(); i++){
        connectBottleneck(outList[i], two->getFinalNode());
    }
    auto *g = new Graph(two->getInitialNode(), one->getFinalNode());
    return g;
}
Graph *GraphGenerator::connectASTRkgraph(Graph *one){
    vector<Edge*> edges = getEdgesOfFour();
    Node *init = new Node(counter++);
    Node *fin = new Node(counter++);
    connectEdgeWithNodes(init, edges[0], one->getInitialNode());
    connectEdgeWithNodes(init, edges[1], fin);
    connectEdgeWithNodes(one->getFinalNode(), edges[2], one->getInitialNode());
    connectEdgeWithNodes(one->getFinalNode(), edges[3], fin);
    auto *g = new Graph(init, fin);
    return g;
}
Graph *GraphGenerator::connectPLUSgraph(Graph *one){
    Graph *copy = getCopyGraph(one);
    Graph *astrik = connectASTRkgraph(one);
    Graph *plus = connectANDgraph(astrik, copy);
    return plus;
}

void GraphGenerator::connectEdgeWithNodes(Node *one, Edge *edg, Node *two){
    edg->toNode(two);
    one->addToOutlist(edg);
}
vector<Edge*> GraphGenerator::getEdgesOfFour(){
    vector<Edge*> edges;
    for(int i = 0; i < 4; i++){
        Edge *ed = new Edge("L");
        edges.push_back(ed);
    }
    return edges;
}

void GraphGenerator::connectBottleneck(Edge *edg, Node *node){
    node->addToOutlist(edg);
}

Graph *GraphGenerator::getCopyGraph(Graph *grph){
    queue<Node*> que;
    set<Node*> nodSet;
    Node *orgstart = grph->getInitialNode();
    Node *copStart = new Node(counter++), *copEnd;
    orgstart->setCopy(copStart);
    que.push(orgstart);
    nodSet.insert(orgstart);
    while(!que.empty()){
        Node *src = que.front();
        que.pop();
        for(int i = 0; i < src->getEdgeOutList().size(); i++){
            Edge *ed = new Edge(src->getEdgeOutList()[i]->getValue());
            Node *dist;
            if(nodSet.find(src->getEdgeOutList()[i]->getToNode()) != nodSet.end()){
                dist = src->getEdgeOutList()[i]->getToNode()->getCopy();
            }else{
                dist = new Node(counter++);
                nodSet.insert(src->getEdgeOutList()[i]->getToNode());
                src->getEdgeOutList()[i]->getToNode()->setCopy(dist);
                que.push(src->getEdgeOutList()[i]->getToNode());
                if(src->getEdgeOutList()[i]->getToNode()->getEdgeOutList().size()== 0){
                    copEnd = dist;
                }
            }
            connectEdgeWithNodes(src->getCopy(), ed, dist);

        }

    }
    auto *g = new Graph(copStart, copEnd);
    nodSet.clear();
    return g;
}