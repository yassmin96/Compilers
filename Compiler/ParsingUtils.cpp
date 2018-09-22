//
// Created by Lenovo on 4/17/2018.
//

#include "ParsingUtils.h"

string ParsingUtils::removeExtraSpaces(string line) {
    char *in = new char[line.length() + 1];
    strcpy(in, line.c_str());
    char out[0x255];
    int inputIndex = 0, outputIndex = 0;
    while(in[inputIndex] != '\0') {
        out[outputIndex] = in[inputIndex];
        if(in[inputIndex] == ' ') {
            while(in[inputIndex + 1] == ' ') {
                inputIndex++;
            }
        }
        outputIndex++;
        inputIndex++;
    }
    out[outputIndex] = '\0';
    string sLine(out);
    delete [] in;
    return sLine;
}

vector<string> ParsingUtils::splitOn(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

template<typename Out> void ParsingUtils::split(const string &s, char delim, Out result) {
    stringstream ss(s);
    string str;
    while (getline(ss, str, delim)) {
        *(result++) = str;
    }
}

void ParsingUtils::replaceAll(string &str, const string from, const string to) {
    unsigned int start_pos = 0;
    while((start_pos = str.find(from,  start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

string ParsingUtils::trim(const string str) {
    return trim_left(trim_right(str));
}

string ParsingUtils::trim_left(const string str) {
    const string pattern = " \f\n\r\t\v";
    return str.substr(str.find_first_not_of(pattern));
}

string ParsingUtils::trim_right(const string str) {
    const string pattern = " \f\n\r\t\v";
    return str.substr(0, str.find_last_not_of(pattern) + 1);
}
