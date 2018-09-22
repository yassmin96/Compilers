//
// Created by Nada_Ayman  on 3/15/2018.
//

#include "FileHandler.h"

FileHandler::FileHandler() {
    blank = new regex("(\\s*\\n*\\t*)*");
}
vector<string> FileHandler::readLanguage(string file){
    ifstream in(file);
    string line;
    vector<string> list;
    while (getline(in, line)) {
        if (regex_match(line, *blank)) continue;
        list.push_back(line);
    }
    return list;
}
