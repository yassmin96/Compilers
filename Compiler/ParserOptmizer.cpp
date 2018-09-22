//
// Created by user on 4/20/2018.
//

#include "ParserOptmizer.h"
ParserOptmizer::ParserOptmizer(map<string, vector<vector<string>>> parsGrammar, set<string> prodSet){
    this->prodSet = prodSet;
    elimnateLeftRecursion(parsGrammar);
    elimnateLeftFactor();
    grammarRec.clear();
}
void ParserOptmizer::elimnateLeftRecursion(map<string, vector<vector<string>>> parsGrammar) {
    for(auto prod : parsGrammar){
        if(grammarRec.find(prod.first) == grammarRec.end()){
            removeLeftRecursion(parsGrammar, prod.first);
            vis.erase(prod.first);
        }
    }
}

vector<vector<string>> ParserOptmizer::removeLeftRecursion(map<string, vector<vector<string>>> parsGrammar, string start){
    vector<vector<string>> vOut;
    if(vis.find(start) != vis.end())
        return makeStrVectorOfVector(start);
    if (vis.find(start) == vis.end()) {
        vis.insert(start);
        if(grammarRec.find(start) != grammarRec.end())
            return grammarRec[start];
        for (int i = 0; i < parsGrammar[start].size(); i++) {
            vector<vector<string>> mulProd;
            if (prodSet.find(parsGrammar[start][i][0]) != prodSet.end() && parsGrammar[start][i][0] != start){
                mulProd = addStrToEachVector(removeLeftRecursion(parsGrammar, parsGrammar[start][i][0]), parsGrammar[start][i]);
                vOut.insert(vOut.end(), mulProd.begin(), mulProd.end());
                vis.erase(parsGrammar[start][i][0]);
            } else {
                vOut.push_back(parsGrammar[start][i]);
            }
        }
        return grammarRec[start] = elimnateImmediateRecursion(vOut, start);
    }
}

vector<vector<string>>ParserOptmizer::elimnateImmediateRecursion(vector<vector<string>> vec, string prod){
    map<string, vector<int>> mpRet = firstidx(vec);
    if(mpRet.find(prod) != mpRet.end()) {
        vector<vector<string>> vOut;
        string newProd = createNewProdName(prod, "#", "#");
        for (auto v : mpRet) {
            if (v.first != prod) {
                for(int i : v.second){
                    vOut.push_back(addStringToVector(vec[i], newProd, 0));
                }
            } else{
                createProdRec(newProd, v.second,vec);
            }
        }
        return vOut;
    }
    return vec;
}

void ParserOptmizer::createProdRec(string prod, vector<int> idx, vector<vector<string>> vec){
    prodSet.insert(prod);
    vector<vector<string>> vOut;
    for(int i : idx){
        vOut.push_back(addStringToVector(vec[i], prod, 1));
    }
    vOut.push_back(makeStrVector(EPS));
    grammarRec[prod] = vOut;
}

void ParserOptmizer::elimnateLeftFactor() {
    for(auto g : grammarRec){
        removeLeftFactor(g.first, g.second);
    }
}
void ParserOptmizer::removeLeftFactor(string g, vector<vector<string>> v){
    map<string, vector<int>> mpidx = firstidx(v);
    conctainateLeftFactor(mpidx, v, g);
}


void ParserOptmizer::conctainateLeftFactor(map<string, vector<int>> mpIdx, vector<vector<string>> vec, string nonTerm){
    vector<vector<string>> vOut;
    for(auto v : mpIdx){
        if(v.second.size() == 1){
            vOut.push_back(vec[v.second[0]]);
        }else{
            string newProd =  createNewProdName(v.first, nonTerm, "##");
            vOut.push_back(concatTwoStrInVector(v.first, newProd));
            createProdLeft(newProd, v.second , vec);
        }
    }
    finalGrammar[nonTerm] = vOut;
}

string ParserOptmizer::createNewProdName(string s1, string s2, string s3){
    string s = s1;
    s.insert(s.size(), s2);
    s.insert(s.size(), s3);
    return s;
}

void ParserOptmizer::createProdLeft(string prod, vector<int> idx, vector<vector<string>> vec){
    vector<vector<string>> vOut;
    vOut = copyVector(idx,vec);
    prodSet.insert(prod);
    removeLeftFactor(prod, vOut);
}
