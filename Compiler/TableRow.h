#ifndef TableRow_H
#define TableRow_H

#include <string>
#include <vector>
#include "Node.h"
#include <map>
#include "LexicalParser.h"
class Node;

class TableRow
{

private:
    map<string, TableRow* > transition;
    vector<Node*> states;
    LexicalParser *lp;

public:
    TableRow(vector<Node*> s, LexicalParser *lngParser);
    void addToArrayList(Node* n);
    void addToHash(string key, TableRow* value);
    map <string,TableRow*> getMap();
    vector<Node*> getArrayList();
    void setType( string T);
    void editMap(string val, Node* n);
    bool isFinal();
    void setFinal(bool f, string T);
    void printMap(string key);
    bool findElement(Node* n);
    string getType();
    string Type;
    bool Final;
    int number;
    void setStateNumber(int n);
    int getStateNumber();
};

#endif // TableRow_H
