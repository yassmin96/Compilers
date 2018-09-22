#include <iostream>
#include "NFAGenerator.h"
#include "FileHandler.h"
#include "LexicalParser.h"
#include "DFAGenerator.h"
#include "SyntaxParser.h"
#include "ParserOptmizer.h"
#include "FirstFollow.h"
#include "ParserTreeGenerator.h"
#include "tokensGenerator.h"

using namespace std;
int main()
{

    FileHandler fh;
    vector<string> lexical = fh.readLanguage("lang.txt");
    vector<string> lines = fh.readLanguage("syntax");
    LexicalParser *lp = new LexicalParser(lexical);
    SyntaxParser *fp = new SyntaxParser(lines);
    ParserOptmizer *po = new ParserOptmizer(fp->productions, fp->getNonTerminals());
    FirstFollow ff(po->finalGrammar, fp->start);
    NFAGenerator *nfa = new NFAGenerator();
    nfa->generateNFA(lp->post, lp->reserved, lp->punc);
    ParserTreeGenerator *fg = new ParserTreeGenerator(ff.PT, fp->start, po->prodSet);
    DFAGenerator *dfa = new DFAGenerator( nfa->startNode , lp,fg);
    tokensGenerator *tg = new tokensGenerator("tokens.txt");
    tg->readProgram(dfa);

    return 0;
}
