
#include "StringVectorUtilis.h"

vector<vector<string>> StringVectorUtilis::copyVector(vector<int> idx, vector<vector<string>> vec){
    vector<vector<string>> vOut;
    for(unsigned int i = 0; i < idx.size(); i++){
        vector<string> vIn;
        if(vec[idx[i]].size() == 1)
            vIn.push_back(EPS);
        else {
            vIn.insert(vIn.end(), vec[idx[i]].begin() + 1, vec[idx[i]].end());
        }
        vOut.push_back(vIn);
    }
    return vOut;
}
vector<string> StringVectorUtilis::concatTwoStrInVector(string s1, string s2){
    vector<string> v;
    v.push_back(s1);
    v.push_back(s2);
    return v;
}
map<string, vector<int>> StringVectorUtilis::firstidx(vector<vector<string>> v){
    map<string, vector<int>> mpRet;
    for(int i = 0; i < v.size(); i++){
        mpRet[v[i][0]].push_back(i);
    }
    return mpRet;
}
vector<vector<string>> StringVectorUtilis::addStrToEachVector(vector<vector<string>> mul , vector<string> sing) {
    vector<vector<string>> vec;
    for(int i = 0; i < mul.size(); i++){
        vector<string> inVec;
        inVec.insert(inVec.end(), mul[i].begin(), mul[i].end());
        inVec.insert(inVec.end(), sing.begin() + 1, sing.end());
        vec.push_back(inVec);
    }
    return vec;
}
vector<string>StringVectorUtilis::addStringToVector(vector<string> v, string s, int vIdx){
    vector<string> vIn;
    vIn.insert(vIn.end(), v.begin()+vIdx, v.end());
    vIn.insert(vIn.end(), s);
    return vIn;
}
vector<string> StringVectorUtilis::makeStrVector(string s){
    vector<string> v;
    v.push_back(s);
    return v;
}
vector<vector<string>> StringVectorUtilis::makeStrVectorOfVector(string s){
    vector<vector<string>> v;
    v.push_back(makeStrVector(s));
    return v;
}