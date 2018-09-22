
#ifndef COMPILER_TOKENSGENERATOR_H
#define COMPILER_TOKENSGENERATOR_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "DFAGenerator.h"
using namespace std;

class tokensGenerator
{
public:
    tokensGenerator(string file);
    void readProgram(DFAGenerator *d);
    vector <string> s ;

private:
    ifstream program;

};

#endif //COMPILER_TOKENSGENERATOR_H
