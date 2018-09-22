#include "FirstFollow.h"

int counter = 0 ;

FirstFollow::FirstFollow(map<string,vector<vector<string>>> p, string start)
{
    PT = new parseTable();

    productions = p;
    for (map<string,vector<vector<string>>> ::iterator it = productions.begin();  counter < productions.size()
                                                                                  && it != productions.end(); ++it)
    {
        counter++;
        First(it->first);
    }
    Follow(start);
    addFollowDependencies();
    completeTable();
    PT->printTable();
}

void FirstFollow::First(string key)
{
    if (firstMap.find(key) != firstMap.end())
        return;
    /// iterate on the vector of strings to get the first letters
    vector<vector<string>> v = productions[key];


    for(int i = 0 ; i <v.size() ; i++)
    {

        vector<string> x = v[i];
        int j = 0;
        string s;
        bool found;

        do
        {
            s = x[j];
            j++;
            found = false;

            if (productions.find(s) != productions.end())
            {
                if(firstMap.find(s) != firstMap.end())
                {
                    for(int i = 0 ; i < firstMap[s].size() ; i++ )
                    {
                        if(!exist(firstMap,key,firstMap[s][i]))
                        {
                            firstMap[key].push_back(firstMap[s][i]);
                            if(firstMap[s][i] == "\\L")
                            { found = true;
                                //cout<< " no recursion variable "<<s << " gave me an epsilon to "<<key<<endl;
                                tableEps.push_back(key);
                            }

                            else
                                PT->fillTable(key, firstMap[s][i], x );
                        }
                    }
                }
                else
                {
                    First(s);
                    if(firstMap.find(key) == firstMap.end())
                    {
                        vector<string> vec ;
                        firstMap[key] = vec;
                    }
                    for(int i = 0 ; i < firstMap[s].size() ; i++ )
                    {
                        if(!exist(firstMap,key,firstMap[s][i]))
                        {
                            firstMap[key].push_back(firstMap[s][i]);
                            if(firstMap[s][i] == "\\L")
                            {   found=true;
                                tableEps.push_back(key);
                            }


                            else
                                PT->fillTable(key, firstMap[s][i], x );
                        }
                    }
                }

            }


            if(firstMap.find(key) == firstMap.end())
            {
                vector<string> vec ;
                firstMap[key] = vec;
            }

            /// add the character
            if(productions.find(s) == productions.end() && ! exist(firstMap,key,s) )
            {
                firstMap[key].push_back(s);

                if(s == "\\L")
                {
                    tableEps.push_back(key);
                }

                else
                    PT->fillTable(key, s, x );
            }
        }
        while( (s == "\\L" || found )&& j<x.size());

    }
}
void FirstFollow::Follow(string start)
{

    for (map<string,vector<vector<string>>> ::iterator it = productions.begin(); it != productions.end(); ++it)
    {
        string nonTerminal = it->first;
        if(followMap.find(nonTerminal) == followMap.end())
        {
            if(nonTerminal == start)
                followMap[start].push_back("$");
            findFollow(nonTerminal);
        }
    }
}
void FirstFollow::findFollow(string key)
{
    for (map<string,vector<vector<string>>> ::iterator it = productions.begin(); it != productions.end(); ++it)
    {
        vector<vector<string>> v = it->second;
        for(int i = 0 ; i < v.size() ; i++)
        {
            vector<string> expr = v[i];
            for(int j = 0 ; j < expr.size() ; j++)
            {


                if(expr[j] == key && j == expr.size()-1 && followBool[it->first] && key != it->first)
                {
                    dependencies[key].push_back(it->first);
                    dependencies[it->first].push_back(key);
                    for(int g =0 ; g < dependencies[key].size() ; g++)
                    {
                        dependencies[it->first].push_back(dependencies[key][g]);
                    }
                    for(int g =0 ; g < dependencies[it->first].size() ; g++)
                    {
                        dependencies[key].push_back(dependencies[it->first][g]);
                    }
                }
                if(expr[j] == key && j == expr.size()-1 && !followBool[it->first] && key != it->first)  ///final term in production
                {
                    followBool[key] = true;

                    if(followMap.find(it->first) == followMap.end())
                        findFollow(it->first);

                    followBool[key] = false;
                    for(int k = 0 ; k < followMap[it->first].size() ; k++ )
                    {
                        if(!exist(followMap,key,followMap[it->first][k]))
                            followMap[key].push_back(followMap[it->first][k]);
                    }

                }
                else if(j+1 < expr.size() && expr[j] == key && productions.find(expr[j+1] ) != productions.end())   ///term after KEY is Non-terminal
                {
                    vector<string> firsts = firstMap[expr[j+1]];
                    for(int k = 0 ; k < firsts.size() ; k++)
                    {
                        if(firsts[k] == "\\L")    /// first has eps. -> get follow
                        {
                            followBool[key] = true;
                            if(followMap.find(expr[j+1]) == followMap.end())
                            {
                                findFollow(expr[j+1]);
                            }


                            followBool[key] = false;
                            if(followMap[expr[j+1]].size() == 0 ||  dependencies.find(expr[j+1]) != dependencies.end())
                            {
                                dependencies[key].push_back(expr[j+1]);
                                cout << key <<  "  Depends on  " << expr[j+1] << endl;
                                for(int g =0 ; g < dependencies[expr[j+1]].size() ; g++)
                                {
                                    dependencies[key].push_back(dependencies[expr[j+1]][g]);
                                }
                            }
                            for(int k = 0 ; k < followMap[expr[j+1]].size() ; k++ )
                            {
                                if(!exist(followMap,key,followMap[expr[j+1]][k]))
                                    followMap[key].push_back(followMap[expr[j+1]][k]);
                            }
                        }
                        else
                        {
                            if(!exist(followMap, key, firsts[k]))
                                followMap[key].push_back(firsts[k]);
                        }
                    }
                }
                else if (j+1 < expr.size() && expr[j] == key && productions.find(expr[j+1] ) == productions.end()) ///term after KEY is terminal
                {

                    if(followMap.find(key) == followMap.end())
                    {
                        vector<string> vec ;
                        followMap[key] = vec ;
                    }
                    if(!exist(followMap, key, expr[j+1]))
                        followMap[key].push_back(expr[j+1]);
                }
            }
        }
    }
}
void FirstFollow::addFollowDependencies()
{
    for (map<string,vector<string>> ::iterator it = dependencies.begin() ;  it != dependencies.end(); ++it)
    {
        for(int k =0 ; k< it->second.size(); k++)
        {
            string s = (it->second)[k];
            for(int i=0; i <followMap[s].size() ; i++)
            {
                if(!exist(followMap, it->first, followMap[s][i]))
                    followMap[it->first].push_back(followMap[s][i]);
            }
        }
    }
}

bool FirstFollow::exist(map<string,vector<string>> m, string nonTerminal, string s)
{
    for(int i =0; i< m[nonTerminal].size() ; i++)
    {
        if(m[nonTerminal][i] == s)
            return true;
    }
    return false;
}

void FirstFollow::printFirst()
{
    for (map<string,vector<string>> ::iterator it = firstMap.begin() ;  it != firstMap.end(); ++it)
    {
        cout<<it->first<<" " ;
        for (int i = 0 ; i < it->second.size() ; i++)
        {
            cout<< it->second.at(i)<< " " ;
        }
        cout<<endl;
    }
}

void FirstFollow::printFollow()
{
    for (map<string,vector<string>> ::iterator it = followMap.begin() ;  it != followMap.end(); ++it)
    {
        cout<<it->first<<" " ;
        for (int i = 0 ; i < it->second.size() ; i++)
        {
            cout<< it->second.at(i)<< " " ;
        }
        cout<<endl;
    }

}
void FirstFollow::completeTable()
{   vector<string>temp ;
    temp.push_back("\\L");
    vector<string> synch;
    synch.push_back("synch");

    for(int i = 0 ; i < tableEps.size() ; i++)
    {
        vector<string> x = followMap[tableEps[i]];
        for(int j = 0 ; j < x.size() ; j ++){
            PT->fillTable(tableEps[i] , x[j], temp);

        }
    }

    for (map<string,vector<vector<string>>> ::iterator it = productions.begin(); it != productions.end(); ++it)
    {
        if(!contains(it->first)){

            vector<string> x = followMap[it->first];
            for(int j = 0 ; j < x.size() ; j ++){
                if(PT->isNull(it->first , x[j]))
                    PT->fillTable(it->first , x[j], synch);

            }
        }
    }

}

bool FirstFollow::contains(string x){

    for(int i=0 ; i< tableEps.size() ; i++){
        if(tableEps[i] == x)
            return true;
    }

    return false;
}