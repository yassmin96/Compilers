//
// Created by user on 4/20/2018.
//

#ifndef PARSER_FILEWRITER_H
#define PARSER_FILEWRITER_H

#include <iostream>
#include <fstream>
using namespace std;

class FileWriter {
	
public:
    FileWriter(string fileName);
    void writeFile(string s);
    void closeFile();

private:
    ofstream file;
};


#endif //PARSER_FILEWRITER_H
