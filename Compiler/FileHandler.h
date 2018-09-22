//
// Created by Nada_Ayman on 3/15/2018.
//

#ifndef COMPILER_FILEHANDLER_H
#define COMPILER_FILEHANDLER_H

#include <iostream>
#include <fstream>
#include<vector>
#include<string>
#include <cstdio>
#include <regex>

using namespace std;


class FileHandler {

private:
    regex *blank;
	
public:
    FileHandler();
    vector<string> readLanguage(string file);
};


#endif //COMPILER_FILEHANDLER_H
