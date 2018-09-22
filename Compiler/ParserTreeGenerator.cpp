
#include "ParserTreeGenerator.h"
enum ENUMS{TERMINAL_ERROR, TERMINAL_MATCH , NONETERMINAL_MATCH, NONETERMINAL_ERROR, NONETERMINAL_SYNCH, NONETERMINAL_EPS};

ParserTreeGenerator::ParserTreeGenerator(parseTable *table, string start, set<string> nonTerminlas){
    this->table = table;
    this->nonTerminlas = nonTerminlas;
    endParsing = false;
    treeHandler1 = new treeHandler(&prodstack, &terminals);
    pushStart(start);
}
void ParserTreeGenerator::parseToken(string token){
    if(!endParsing) {
        if (prodstack.empty() || notAcceptedProg(token)) {
            treeHandler1->errorSubRoutineNotAcpt();
            treeHandler1->endParsing();
            endParsing = true;
        } else {
            string top = prodstack[prodstack.size() - 1];
            int cmpRet = compare(top, token);
            switchCases(cmpRet, top, token);
        }
        checkEndingParsing(token);
    }
}
void ParserTreeGenerator::switchCases(int cmpRet, string top, string token){
    switch (cmpRet) {
        case TERMINAL_ERROR:
            terminalError(top, token);
            break;
        case NONETERMINAL_MATCH:
            nonTerminalMatch(top, token);
            break;
        case TERMINAL_MATCH:
            terminalMatch(top, token);
            break;
        case NONETERMINAL_ERROR:
            nonTerminalError(top, token);
            break;
        case NONETERMINAL_EPS:
            nonTerminalEps(top, token);
            break;
        default:
            nonTerminalSynch(top, token);

    }
}
void ParserTreeGenerator::terminalMatch(string top, string token){
    prodstack.pop_back();
    terminals.push_back(top);
    treeHandler1->matchInp(token);
}
void ParserTreeGenerator::terminalError(string top, string token){
    prodstack.pop_back();
    treeHandler1->errorSubRoutineTerm(top);
    parseToken(token);
}
void ParserTreeGenerator::nonTerminalMatch(string top, string token){
    prodstack.pop_back();
    reversPush(top, token);
    treeHandler1->buildTree();
    treeHandler1->match(token, top, table->getProduction(top, token));
    parseToken(token);
}
void ParserTreeGenerator::nonTerminalError(string top, string token){
    treeHandler1->errorSubRoutineNonTerm(token);
}
void ParserTreeGenerator::nonTerminalSynch(string top, string token){
    prodstack.pop_back();
    treeHandler1->match(token, top, table->getProduction(top, token));
    parseToken(token);
}
void ParserTreeGenerator::nonTerminalEps(string top, string token){
    prodstack.pop_back();
    treeHandler1->buildTree();
    treeHandler1->match(token, top, table->getProduction(top, token));
    parseToken(token);
}
void ParserTreeGenerator::pushStart(string start){
    prodstack.push_back("$");
    prodstack.push_back(start);
    treeHandler1->buildTree();
}
void ParserTreeGenerator::reversPush(string top, string token){
    vector<string> prod = table->getProduction(top, token);
    for(int i = prod.size() - 1; i >= 0 ; i--){
        prodstack.push_back(prod[i]);
    }
}

bool ParserTreeGenerator::inMap(string top){
    return nonTerminlas.find(top) != nonTerminlas.end();
}
int ParserTreeGenerator::compare(string top, string token){
    if(inMap(top)){
        return compareNonTerminals(top, token);
    }
    return compareTerminals(top, token);
}
int ParserTreeGenerator::compareTerminals(string top, string token){
    if(top == token){
        return TERMINAL_MATCH;
    }
    return TERMINAL_ERROR;
}
int ParserTreeGenerator::compareNonTerminals(string top, string token){
    if(table->inTable(top, token)){
        if(table->getProduction(top, token)[0] == "\\L"){
            return NONETERMINAL_EPS;
        }
        else if(table->getProduction(top, token)[0] == "synch") {
            return NONETERMINAL_SYNCH;
        }
        return NONETERMINAL_MATCH;
    }

    return NONETERMINAL_ERROR;
}

bool ParserTreeGenerator::notAcceptedProg(string token){
    string top = prodstack[prodstack.size() - 1];
    return token == "$" && inMap(top) && !table->inTable(top, token);
}
void ParserTreeGenerator::checkEndingParsing(string token){
    if(prodstack.empty() && token == "$"){
        treeHandler1->endParsing();
    }
}
