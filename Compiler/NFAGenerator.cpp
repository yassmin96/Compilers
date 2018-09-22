//
// Created by Dalia on 16/03/2018.
//

#include "NFAGenerator.h"
NFAGenerator::NFAGenerator()
{
    startNode = new Node(0);
    graphGenerator = new GraphGenerator();
}
void NFAGenerator::generateNFA(map<string, vector <string>> post, vector<string> reserved, vector<string> punc){
    createKeywordNFA(reserved);
    createPuncNFA(punc);
    for(map<string,vector<string> >::iterator it = post.begin(); it != post.end(); ++it) {
        createLanguageNFA(it->second, it->first);
    }
}
void NFAGenerator::createPuncNFA(vector<string> punc){
    for(int i = 0; i < punc.size(); i++){
        Graph *pun = graphGenerator->genGraphPunc(punc[i]);
        pun->getFinalNode()->setFinal(punc[i]);
        mergeWthStart(pun->getInitialNode());
    }
}
void NFAGenerator::createKeywordNFA(vector<string> keywords){
    for(int i = 0; i < keywords.size(); i++){
        Graph *word = graphGenerator->genGraphKeyword(keywords[i]);
        word->getFinalNode()->setFinal(keywords[i]);
        mergeWthStart(word->getInitialNode());
    }
}
void NFAGenerator::mergeWthStart(Node *node){
    Edge *edge = new Edge("L");
    graphGenerator->connectEdgeWithNodes(startNode, edge, node);

}
void NFAGenerator::createLanguageNFA(vector<string> grammer, string tokenType){
    Graph *language = evaluatePsitfixToGraph(grammer);
    language->getFinalNode()->setFinal(tokenType);
    mergeWthStart(language->getInitialNode());
}

Graph *NFAGenerator::evaluatePsitfixToGraph(vector<string> grammer){
    vector<Graph*> stack;
    Graph *returned;
    for(int i = 0; i < grammer.size(); i++){
        if(!isOperator(grammer[i])){
            Graph *g = graphGenerator->genLexemGraph(grammer[i]);
            stack.push_back(g);
        }else{
            if(grammer[i] == "|"){
                Graph *one = stack.back();
                stack.pop_back();
                Graph *two = stack.back();
                stack.pop_back();
                returned = graphGenerator->connectORgraph(one, two);
                stack.push_back(returned);
            }else if(grammer[i] == "#"){
                Graph *one = stack.back();
                stack.pop_back();
                Graph *two = stack.back();
                stack.pop_back();
                returned = graphGenerator->connectANDgraph(one, two);
                stack.push_back(returned);
            }else if(grammer[i] == "**"){
                Graph *one = stack.back();
                stack.pop_back();
                returned = graphGenerator->connectASTRkgraph(one);
                stack.push_back(returned);
            }else{
                Graph *one = stack.back();
                stack.pop_back();
                returned = graphGenerator->connectPLUSgraph(one);
                stack.push_back(returned);
            }
        }
    }
    Graph *r = stack.back();
    stack.pop_back();
    return r;
}
bool NFAGenerator::isOperator(string s){
    return (s == "|" || s == "**" || s == "++" || s == "#");
}
void NFAGenerator::print(){
    queue<Node*> que;
    set<Node*> nodSet;
    for(int j = 0; j < startNode->getEdgeOutList().size(); j++) {
        Node *orgstart = startNode->getEdgeOutList()[j]->getToNode();
        que.push(orgstart);
        nodSet.insert(orgstart);
        while (!que.empty()) {
            Node *src = que.front();
            que.pop();
            for (int i = 0; i < src->getEdgeOutList().size(); i++) {
                if (nodSet.find(src->getEdgeOutList()[i]->getToNode()) != nodSet.end()) {
                } else {
                    que.push(src->getEdgeOutList()[i]->getToNode());
                    nodSet.insert(src->getEdgeOutList()[i]->getToNode());
                }
            }
        }
        nodSet.clear();
    }
}
