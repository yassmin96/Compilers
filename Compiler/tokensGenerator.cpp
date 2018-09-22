
#include "TokensGenerator.h"
tokensGenerator::tokensGenerator(string file)
{
    program.open(file);
}
void tokensGenerator::readProgram(DFAGenerator *d)
{
    int i = 0;
    char c;
    while (program.get(c))
    {
        if(c !='\0' && (c=='\n' || c=='\r' || c =='\t'))
        {
            s.push_back(" ");
            i++;
        }
        if(c !='\0' && c != '\n' && c != '\r' && c != '\t')
        {
            s.push_back(string(1, c));
            i++;
        }
    }
    d->findToken(s);
}
