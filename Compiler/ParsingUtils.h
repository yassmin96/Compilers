//
// Created by Lenovo on 4/17/2018.
//

#ifndef COMPILER_PARSINGUTILS_H
#define COMPILER_PARSINGUTILS_H

#include <string>
#include <stack>
#include <vector>
#include <map>
#include <cstring>
#include <iostream>
#include <regex>

using namespace std;

namespace ParsingUtils {
    template<typename Out> void split(const string &s, char delim, Out result);
    string removeExtraSpaces(string line);
    string trim(const string str);
    string trim_left(const string str);
    string trim_right(const string str);
    void replaceAll(string &str, const string from, const string to);
    vector<string> splitOn(const string &s, char delim);
};


#endif //COMPILER_PARSINGUTILS_H
