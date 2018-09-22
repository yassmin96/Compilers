#include "TableRow.h"

TableRow::TableRow(vector<Node*> s,LexicalParser *lngParser)
{
    states = s;
    Final = false;
    lp = lngParser;
}

vector<Node*> TableRow::getArrayList()
{
    return states;
}

void TableRow::addToArrayList(Node* n)
{
    states.push_back(n);
}
int TableRow::getStateNumber()
{
    return number;
}
void TableRow::setStateNumber(int n)
{
    number = n;
}

void TableRow::addToHash(string key, TableRow* value)
{
    transition[key] = value;
}
map <string,TableRow*> TableRow::getMap()
{
    return transition;
}
void TableRow:: editMap(string val, Node* n)
{
    transition[val]->addToArrayList(n);
}

bool TableRow::isFinal()
{
    return Final;
}
void TableRow::setFinal(bool f, string T)
{
    if(!Final)
    {
        Type = T;
    }
    else if ( (lp->priority).find(T) != (lp->priority).end() && (lp->priority).find(Type) != (lp->priority).end()
              && ((lp->priority)[T]) <= ((lp->priority)[Type]))
    {
        Type = T;
    }
    Final = true;

}
void TableRow::setType( string T)
{
    Type = T;

}
void TableRow::printMap(string key)
{

    for( int p = 0 ; p < transition[key]->getArrayList().size(); p++)
    {

        cout << (transition[key]->getArrayList()[p]->getNodeCount())<< " " ;
    }
    cout << endl;

}
string TableRow::getType()
{
    return Type;
}
bool TableRow::findElement(Node* n)
{
    return std::find(states.begin(), states.end(), n) != states.end();
}

