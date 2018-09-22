//
// Created by Lenovo on 4/18/2018.
//

#include "SyntaxParser.h"


SyntaxParser::SyntaxParser(vector<string> l){
    lines = l;
    Parse();
}

void SyntaxParser::Parse(){
    string key;
    for(string value : lines) {
        replaceAll(value, "'", "");
        vector<string> v;
        if(value[0] == '#'){
            unsigned int equals = value.find('=');
            key = value.substr(2, equals - 3);
            if(start == "") start = key;
            vector<string> orSplitting = splitOn(trim(value.substr(equals + 1, value.length() - 1)), '|');
            for(string x : orSplitting) {
                vector<string> spaceSplitting = splitOn(trim(x), ' ');
                productions[key].push_back(spaceSplitting);
            }
        }else {
            vector<string> orSplitting = splitOn(trim(value.substr(1, value.length() - 1)), '|');
            for(string x : orSplitting) {
               vector<string> spaceSplitting = splitOn(trim(x), ' ');
               productions[key].push_back(spaceSplitting);
            }
        }
    }
}

set<string> SyntaxParser::getNonTerminals(){
    set<string> nonTerminals;
    for (map<string,vector<vector<string> > >::iterator it = productions.begin(); it != productions.end(); ++it) {
        nonTerminals.insert(it->first);
    }
    return nonTerminals;
}


