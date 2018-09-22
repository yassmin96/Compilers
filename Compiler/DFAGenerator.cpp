
#include "DFAGenerator.h"



DFAGenerator::DFAGenerator(Node* s, LexicalParser *lngParser, ParserTreeGenerator *pt)
{
    this->parserTree = pt;
    vector<Node*> temp;
    temp.push_back(s);
    TableRow* x = new TableRow(temp, lp);
    states.push_back(x);
    x->setStateNumber(states.size());
    lp = lngParser;
    states[0] = Eclosure(states[0]);

    if(s->isFinal())
    {
        states[0]->setFinal(true, s->getFinalType());
    }
    tableGenerator();

    Minimize();

    for( int k =0 ; k < states.size() ; k++)
    {
        map<string,TableRow*> mm = states[k]->getMap();
        int counter = 0;
        int x = mm.size();
        for(map<string,TableRow*>::iterator itr = mm.begin(); counter < x && itr != mm.end()
                ; ++itr)
        {
            if (itr->second->getStateNumber() == 15 || itr->second->getStateNumber() == 40 || itr->second->getStateNumber() == 45)
            {
                for(int y =0;  y<itr->second->getArrayList().size() ; y++)
                {
                    //cout << itr->second->getArrayList()[y]->getNodeCount() << " "  ;
                }
                //cout << endl;
            }
        }
    }
}

TableRow* DFAGenerator::Eclosure(TableRow *row)
{
    stack<Node*> Stack;
    vector<Node*> temp;
    TableRow *newRow = new TableRow(temp,lp);
    for(int i = 0 ; i < row->getArrayList().size() ; i++)
    {
        Stack.push(row->getArrayList()[i]);
        newRow->addToArrayList(row->getArrayList()[i]);

        if(row->getArrayList()[i]->isFinal())
        {
            newRow->setFinal(true, row->getArrayList()[i]->getFinalType());
        }
    }
    while(!Stack.empty())
    {
        Node* n = Stack.top();
        Stack.pop();
        vector<Edge*> edges = n->getEdgeOutList();
        for(int i = 0 ; i< edges.size() ; i++)
        {
            Edge* e = edges[i];
            if(e->getValue() == "L")
            {
                if(!newRow->findElement(e->getToNode()))
                {
                    newRow->addToArrayList(e->getToNode());
                    Stack.push(e->getToNode());
                    if(e->getToNode()->isFinal())
                    {
                        newRow->setFinal(true, e->getToNode()->getFinalType() );
                    }
                }
            }
        }
    }
    return newRow;
}
int DFAGenerator:: countSame(vector<Node*> one, vector<Node*> two)
{
    int counter = 0 ;
    for (int i = 0 ; i < one.size() ; i ++)
    {
        if(std::find(two.begin(), two.end(), one[i]) != two.end())
        {
            counter++;
        }
        else
        {
            counter = -1 ;
            break;
        }
    }
    return counter;
}

void DFAGenerator::tableGenerator()
{
    for(int i = 0 ; i < states.size(); i++)
    {
        TableRow *row = states[i];
        vector<Node*> state = row->getArrayList();
        for (int j = 0 ; j < state.size() ; j++ )
        {
            Node* n = state[j];
            vector<Edge*> edgeList = n->getEdgeOutList();
            for(int k = 0 ; k < edgeList.size() ; k++ )
            {
                Edge* e = edgeList[k];
                string val = e->getValue();
                map<string,TableRow*> temp = row->getMap();
                if(val != "L")
                {
                    if(temp[val] == NULL)
                    {
                        vector<Node*> t;
                        t.push_back(e->getToNode());
                        TableRow* tempr = new TableRow(t,lp);
                        row->addToHash(val,tempr);
                    }
                    else
                    {
                        row->editMap(val,e->getToNode());
                    }
                }
            }
        }
        int coun = 0;
        map<string,TableRow*> mm = row->getMap();
        int x =  mm.size();
        for(map<string,TableRow*>::iterator itr = mm.begin(); coun < x && itr != mm.end(); ++itr)
        {
            string key = itr->first;
            coun++;
            TableRow *r = Eclosure(itr->second);
            row->addToHash(key,r);
            bool stateFound = false;
            for(int k = 0 ; k < states.size(); k++)
            {
                if(countSame(states[k]->getArrayList(), r->getArrayList()) == r->getArrayList().size())
                {
                    stateFound = true;
                    row->addToHash(key,states[k]);
                    break;
                }
            }
            if(!stateFound)
            {
                states.push_back(row->getMap()[key]);
                row->getMap()[key]->setStateNumber(states.size());
            }
        }
    }
}

void DFAGenerator::Minimize()
{
    for(int i = 0 ; i < states.size()-1; i++)
    {
        bool found =false;
        TableRow* Row1 = states[i];
        map<string,TableRow*> Row1map = Row1->getMap();
        for(int j =i+1 ; j < states.size() ; j++)
        {
            TableRow* Row2 = states[j];
            int counter1, counter2;
            map<string,TableRow*> Row2map = Row2->getMap();
            if(Row1map.size() == Row2map.size() && Row1->isFinal() == Row2->isFinal() )
            {
                counter1 = 0;
                for(map<string,TableRow*>::iterator it = Row1map.begin(); counter1 < Row1map.size() && it != Row1map.end(); ++it)
                {
                    found = false;
                    counter2 =0;
                    for (map<string,TableRow*>::iterator it2 = Row2map.begin(); counter2 < Row2map.size() &&it2 != Row2map.end(); ++it2)
                    {
                        if (it->first == it2->first && it->second == it2->second)
                        {
                            found = true;
                        }
                        counter2++;
                    }
                    if(!found)
                    {
                        break;
                    }
                    counter1++;
                }
                if(found)  // 2 identical states
                {
                    for(int k = 0 ; k < states.size()-1; k++)
                    {
                        TableRow* ro = states[k];
                        int counter3 = 0;
                        map<string,TableRow*>rowMap = ro->getMap();
                        for (map<string,TableRow*>::iterator iter = rowMap.begin(); counter3 < rowMap.size() && iter != rowMap.end(); ++iter)
                        {
                            if ((iter->second)->getArrayList() == Row2->getArrayList())
                            {
                                ro->addToHash(iter->first, Row1);
                            }
                            counter3++;
                        }
                    }
                    if(states[i]->isFinal() && lp->priority[states[j]->getType()] < lp->priority[states[i]->getType()])
                    {
                        states[i]->setType(states[j]->getType());
                    }
                    states.erase(states.begin() + j);
                    j--;
                }
            }
        }
    }
}

void DFAGenerator::findToken(vector <string> s)
{

    TokenPath* x = new TokenPath();
    TableRow* rr = states[0];
    x->addNodeToPath(rr);
    tokPath.push_back(x);
    int i = 0 ;
    for(i; i < s.size() ; i++)
    {
        TokenPath* newPath = new TokenPath();
        vector <TableRow*> tr = tokPath.back()->getPath();
        for (int j = 0 ; j < tr.size() ; j++)
        {
            int counter = 0;
            map<string,TableRow*> rowMap = tr[j]->getMap();
            for (map<string,TableRow*>::iterator iter = rowMap.begin(); counter < rowMap.size()&&iter != rowMap.end(); ++iter)
            {
                counter++;
                const char *cstr = (iter->first).c_str();
                string str(cstr);
                if(s[i] != " " && "letter" == (iter->first)
                   && ((s[i] >= "a" && s[i] <= "z") || (s[i] >= "A" && s[i] <= "Z")))
                {
                    adder(newPath, iter->second, i);
                }


                else if(s[i] != " " && "digit" == (iter->first)
                        && (s[i] >= "0" && s[i] <= "9"))
                {
                    adder(newPath, iter->second, i);
                }
                else if(s[i] != " " && s[i]== (iter->first ))
                {
                    adder(newPath, iter->second, i);
                }
            }
        }

        if( (newPath->pathSize() == 0 || i == s.size()-1)  )
        {
            if(i == s.size()-1)
            {
                tokPath.push_back(newPath);
            }
            for(int k=tokPath.size()-1 ; k >= 0 ; k--)
            {
                if(tokPath[k]->hasFinal())
                {
                    cout<< tokPath[k]->getFinalNode()->getType()<<endl;
                    parserTree->parseToken(tokPath[k]->getFinalNode()->getType());
                    TokenPath* x = new TokenPath();
                    TableRow* rr = states[0];
                    x->addNodeToPath(rr);
                    tokPath.push_back(x);
                    if(!tokPath[k]->isAcceptedUsed())
                        i=tokPath[k]->getAcceptedCharIndex();
                    else {
                        i++;
                        cout << "Token ERROR" << endl;
                    }
                    while(i+1 < s.size() && (s[i+1] == " "))
                    {
                        i++;
                    }
                    break;
                }
            }
        }
        else
        {
            tokPath.push_back(newPath);
        }

    }
    parserTree->parseToken("$");
}
void DFAGenerator::adder (TokenPath *newPath,TableRow* iterSecond, int i )
{
    newPath->addNodeToPath(iterSecond);
    if((iterSecond)->isFinal())
    {
        if(newPath->hasFinal() &&
           (lp->priority[newPath->getFinalNode()->getType()] ) >
           (lp->priority[iterSecond->getType()]))
        {
            newPath->setFinalNode(iterSecond);
            newPath->setAcceptedCharIndex(i);
        }
        else if (!newPath->hasFinal())
        {
            newPath->setFinalNode(iterSecond);
            newPath->setAcceptedCharIndex(i);
        }
    }
}
