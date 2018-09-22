//
// Created by user on 4/20/2018.
//

#include "treeHandler.h"

treeHandler::treeHandler(vector<string> *prodstack, vector<string> *terminals){
    tree = new FileWriter("tree.txt");
    logs = new FileWriter("logs.txt");
    this->prodstack = prodstack;
    this->terminals = terminals;
    treeSize = 1;
}
void treeHandler::errorSubRoutineTerm(string token){
    logs->writeFile("ERROR: missing  " + token + "  ,inserted  in Line: " + to_string(treeSize) + "\n");
}
void treeHandler::errorSubRoutineNonTerm(string token){
    logs->writeFile("ERROR: illegal, discard  " + token+ "  in Line: "+ to_string(treeSize) +"\n");
}
void treeHandler::errorSubRoutineNotAcpt(){
    logs->writeFile("ERROR: can not compelete parsing\n");
}
void treeHandler::buildTree(){
    for(int i = 0; i < terminals->size(); i++) {
        tree->writeFile(":" +terminals->at(i)+":" + " ");
    }
    for(int i = prodstack->size() - 1; i > 0; i--) {
        tree->writeFile(prodstack->at(i) + " ");
    }
    treeSize++;
    tree->writeFile("\n");
}
void treeHandler::match(string token, string top, vector<string> prod){
    ostringstream  production;
    copy(prod.begin(), prod.end(), ostream_iterator<string>(production, " "));
    logs->writeFile("PARSING : " + token+ " : " +top + "  --->  "+production.str() +" \n");
}
void treeHandler::matchInp(string token){
    logs->writeFile("MATCHING INPUT: " +token+ "\n");
}
void treeHandler::endParsing(){
    logs->closeFile();
    tree->closeFile();
}