#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include "token.h"
#include "SyntaxError.h"

class Translator
{
public:
    Translator(std::string exp);
    std::vector<Token> translate();
private:
    std::string expression;
};


#endif // TRANSLATOR_H
