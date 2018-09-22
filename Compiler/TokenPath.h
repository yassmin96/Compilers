#ifndef TOKENPATH_H
#define TOKENPATH_H
#include "TableRow.h"

class TokenPath
{
public:
    TokenPath();
    int char_index ;
    TableRow* current_final;
    void addNodeToPath(TableRow* r);
    void setFinalNode(TableRow* f);
    void setAcceptedCharIndex(int i);
    bool Final;
    vector<TableRow*> getPath();
    TableRow* getFinalNode();
    int getAcceptedCharIndex();
    bool hasFinal();
    int pathSize();
    bool isAcceptedUsed();

private:
    bool used;
    vector<TableRow*> path;

};

#endif // TOKENPATH_H
