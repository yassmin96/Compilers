//
// Created by user on 4/26/2018.
//

#ifndef COMPILER_STRINGVECTORUTILIS_H
#define COMPILER_STRINGVECTORUTILIS_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include<algorithm>
#include<iterator>
#define EPS "\\L"

using namespace std;

namespace StringVectorUtilis {
    vector<vector<string>> addStrToEachVector(vector<vector<string>> mul , vector<string> sing);
    map<string, vector<int>> firstidx(vector<vector<string>> v);
    vector<string>addStringToVector(vector<string> v, string s, int vIdx);
    vector<string> concatTwoStrInVector(string s1, string s2);
    vector<string> makeStrVector(string s);
    vector<vector<string>> makeStrVectorOfVector(string s);
    vector<vector<string>> copyVector(vector<int> idx, vector<vector<string>> vec);
};


#endif //COMPILER_STRINGVECTORUTILIS_H
