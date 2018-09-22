
#ifndef PARSER_PARSERTREEGENERATOR_H
#define PARSER_PARSERTREEGENERATOR_H

#include <iostream>
#include <string.h>
#include <vector>
#include <set>
#include "parseTable.h"
#include "treeHandler.h"
using namespace std;

class ParserTreeGenerator {
public:
    ParserTreeGenerator(parseTable *table, string start, set<string> nonTerminlas);
    void parseToken(string token);
private:
    vector<string> prodstack;
    vector<string> terminals;
    parseTable *table;
    bool endParsing;
    treeHandler *treeHandler1;
    set<string> nonTerminlas;
    void pushStart(string start);
    void reversPush(string top, string token);
    int compare(string top, string token);
    int compareTerminals(string top, string token);
    int compareNonTerminals(string top, string token);
    void switchCases(int cmpRet, string top, string token);
    void terminalMatch(string top, string token);
    void terminalError(string top, string token);
    void nonTerminalMatch(string top, string token);
    void nonTerminalError(string top, string token);
    void nonTerminalSynch(string top, string token);
    void nonTerminalEps(string top, string token);
    bool notAcceptedProg(string token);
    bool inMap(string top);
    void checkEndingParsing(string token);
};
#endif //PARSER_PARSERTREEGENERATOR_H
