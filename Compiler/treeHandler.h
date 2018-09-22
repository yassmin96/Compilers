
#ifndef PARSER_TREEHANDLER_H
#define PARSER_TREEHANDLER_H
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include "FileWriter.h"
using namespace std;
class treeHandler {
public:
    treeHandler(vector<string> *prodstack, vector<string> *terminals);
    void buildTree();
    void match(string token, string top, vector<string> prod);
    void matchInp(string token);
    void errorSubRoutineTerm(string token);
    void errorSubRoutineNonTerm(string token);
    void endParsing();
    void errorSubRoutineNotAcpt();

private:
    FileWriter *tree;
    FileWriter *logs;
    int treeSize;
    vector<string> *prodstack;
    vector<string> *terminals;
};


#endif //PARSER_TREEHANDLER_H
