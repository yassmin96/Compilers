#include "TokenPath.h"

TokenPath::TokenPath()
{
    used = false;
    Final = false;
}
void TokenPath::addNodeToPath(TableRow* r)
{
    path.push_back(r);
}
void TokenPath::setFinalNode(TableRow* f)
{
    current_final = f ;
    Final = true ;
}
void TokenPath::setAcceptedCharIndex(int i)
{
    char_index = i ;
}
int TokenPath::getAcceptedCharIndex()
{
    used = true;
    return char_index ;
}
bool TokenPath::isAcceptedUsed(){
    return used;
}
bool TokenPath::hasFinal()
{
    return Final ;
}
vector<TableRow*> TokenPath::getPath()
{
    return path;
}
TableRow* TokenPath::getFinalNode()
{
    return current_final;
}
int TokenPath::pathSize()
{
    return path.size();
}
