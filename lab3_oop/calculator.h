#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include "operatorcreator.h"
#include "token.h"


class Calculator
{
public:
    Calculator(std::vector<Token> exp);
    std::string calculate();
private:
    std::vector<Token> expression;
};

#endif // CALCULATOR_H
