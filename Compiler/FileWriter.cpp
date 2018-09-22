//
// Created by user on 4/20/2018.
//

#include "FileWriter.h"
FileWriter::FileWriter(string fileName){
    file.open(fileName);
}
void FileWriter::writeFile(string s){
    file << s;
}
void FileWriter::closeFile(){
    file.close();
}