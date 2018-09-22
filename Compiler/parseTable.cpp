#include "parseTable.h"

parseTable::parseTable()
{
}

void parseTable::fillTable(string nonTerminal , string input , vector<string> production){
    (table[nonTerminal])[input] = production;
}
vector<string> parseTable::getProduction(string nonTerminal , string input){
    return (table[nonTerminal])[input];
}
bool parseTable::inTable(string nonTerminal, string input){

    return table[nonTerminal].find(input) != table[nonTerminal].end();
}
bool parseTable::isNull(string nonTerminal, string input){
    return table[nonTerminal].find(input) == table[nonTerminal].end();
}

void parseTable::printTable()
{
    cout<<"Start Printing";
    cout << table.size()<<endl;
    for (map<string, map<string,vector<string>>>  ::iterator it = table.begin(); it != table.end(); ++it)
    {
        map<string,vector<string>> m = it->second;
        cout << "nonTerminal: "<<it->first << "    ";
        for ( map<string,vector<string>>  ::iterator it2= m.begin(); it2 != m.end(); ++it2)
        {
            cout << "Input: "<< it2->first << " ";
            vector<string> v = it2->second;

            for(int i=0 ; i < v.size() ; i++){
                cout<< v[i];
            }
            cout << "   "<<endl;
        }
    }

}
