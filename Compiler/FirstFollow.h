#ifndef FIRSTFOLLOW_H
#define FIRSTFOLLOW_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "parseTable.h"
using namespace std;

class FirstFollow
{
public:
    FirstFollow(map<string,vector<vector<string>>> p, string start);
    void First(string key);
    map<string,vector<string>> firstMap;
    map<string,vector<string>> followMap;
    map<string,bool> followBool;
    map<string,vector<string>> dependencies;
    map<string,vector<vector<string>>> productions;
    vector<string> tableEps;
    void Follow(string start);
    void printFirst();
    void findFollow(string key);
    void printFollow();
    void completeTable();
    bool contains(string s);
    void addFollowDependencies();
    bool exist(map<string,vector<string>> m , string nonTerminal ,  string s);
    parseTable *PT;


protected:

private:
};

#endif // FIRSTFOLLOW_H
