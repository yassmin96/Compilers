//
// Created by Nada_Ayman on 3/15/2018.
//

#include "LexicalParser.h"

LexicalParser::LexicalParser(vector<string> l){
    lines = l;
    initializeRegex();
    Parse();
}

void LexicalParser::Parse(){
    for(auto value: lines) {
        separate(value);
        replaceAll(value, "\\", " ");
        value = removeExtraSpaces(trim(value));
        if (regex_match(value, *keyword)) {
            vector<string> v = splitOn(trim(value.substr(value.find('{') + 1, value.find('}') - 1)), ' ');
            reserved.insert( reserved.end(), v.begin(), v.end() );
        } else if (regex_match(value, *punctuation)) {
            punc = splitOn(trim(value.substr(value.find('[') + 1, value.find(']') - 1)), ' ');
        } else {
            unsigned int equals = value.find('='), colon = value.find(':');
            if (colon == -1 && equals != -1) {
                if(isRegex(value.substr(equals + 2, value.size()))) {
                    addRegex(value.substr(0, equals - 1), value.substr(equals + 2, value.size()));
                }
                else {
                    basic[value.substr(0, equals - 1)] = value.substr(equals + 2, value.size());
                }
            } else if ((colon != -1 && equals == -1) || (colon < equals)) {
                checkSubstitution(value);
                lang[value.substr(0, colon - 1)] = splitOn(value.substr(colon + 2, value.size()), ' ');
                priority[value.substr(0, colon - 1)] = priority.size();
            }
        }
    }
    for (map<string,vector<string>>::iterator it = lang.begin(); it != lang.end(); ++it) {
        post[it->first] = getPostfix(it->second);
    }
}

void LexicalParser::checkSubstitution(string &s){
    for(auto term : basic) {
        if(s.find(" " + term.first + " ") != -1) {
            replaceAll(s, " " + term.first + " ", " " + term.second + " ");
        }
    }
}

bool LexicalParser::isRegex(string s) {
    vector<string> v = splitOn(s, ' ');
    for(string str : v) {
        if(regs.find(str) != regs.end()) {
            return false;
        }
    }
    return true;
}


void LexicalParser::initializeRegex() {
    keyword = new regex("\\{.*\\}");
    punctuation = new regex("\\[.*\\]");
}

void LexicalParser::addRegex(string key, string val) {
    vector<string> v = splitOn(val, '|');
    vector<string> final;
    for(string s : v) {
        vector<string> tmp = splitOn(s, '-');
        for(string x : tmp) {
            final.push_back(trim(x));
        }
    }
    regs[key] = final;
}

void LexicalParser::separate(string &str){
    replaceAll(str, "(", " ( ");
    replaceAll(str, "=", " = ");
    replaceAll(str, ":", " : ");
    replaceAll(str, ")", " ) ");
    replaceAll(str, "|", " | ");
    replaceAll(str, ".", " . ");
    replaceAll(str, "*", " * ");
    replaceAll(str, "+", " + ");
    replaceAll(str, "\\ +", "\\+");
    replaceAll(str, "\\ *", "\\*");
    replaceAll(str, "\\ = ", "\\=");
    replaceAll(str, "\\ (", "\\(");
    replaceAll(str, "\\ )", "\\)");
    replaceAll(str, " * ", " ** ");
    replaceAll(str, " + ", " ++ ");
}

vector<string> LexicalParser::getPostfix(vector<string> infix) {
    stack<string> S;
    vector<string> postfix;
    for(int i = 0; i < infix.size(); i++) {
        if(isOperator(infix[i])) {
            putOperator(S, postfix, infix[i]);
        } else if (infix[i] == "(") {
            if(i > 0 && infix[i - 1] != "|"){
                putOperator(S, postfix, "#");
            }
            S.push(infix[i]);
        } else if(infix[i] == ")") {
            while(!S.empty() && S.top() !=  "(") {
                postfix.push_back((string)S.top());
                S.pop();
            }
            S.pop();
            if(i < infix.size() - 1 && !isOperator(infix[i + 1])){
                putOperator(S, postfix, "#");
            }
        } else {
            if( i > 0 && infix[i - 1] != "|" && infix[i - 1] != "("){
                putOperator(S, postfix, "#");
            }
            postfix.push_back(infix[i]);
        }
    }
    while(!S.empty()) {
        postfix.push_back((string)S.top());
        S.pop();
    }
    return postfix;
}
void LexicalParser::putOperator(stack<string> &S, vector<string> &v, string str){
    while(!S.empty() && S.top() != "(" && hasHigherPrecedence(S.top(), str)) {
        v.push_back((string)S.top());
        S.pop();
    }
    S.push(str);
}

bool LexicalParser::isOperator(const string s) {
    return s == "++" || s == "#" || s == "**" || s == "|";
}

int LexicalParser::getWeight(const string op) {
    if(op == "**" || op == "++")
        return 3;
    if(op == "#")
        return 2;
    if(op == "|")
        return 1;
    return 0;
}

int LexicalParser::hasHigherPrecedence(string op1, string op2) {
    return getWeight(op1) > getWeight(op2);
}