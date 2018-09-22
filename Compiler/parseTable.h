#ifndef PARSETABLE_H
#define PARSETABLE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class parseTable
{
public:
    parseTable();
    void fillTable(string nonTerminal , string input , vector<string> production);
    vector<string> getProduction(string nonTerminal , string input);
    bool inTable(string nonTerminal, string input);
    void printTable();
    bool isNull(string nonTerminal, string input);
	
private:
    map<string, map<string,vector<string>>> table;
};

#endif // PARSETABLE_H
