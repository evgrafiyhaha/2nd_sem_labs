#ifndef VALIDATIONCHECKER_H
#define VALIDATIONCHECKER_H

#include <string>
#include "operator.h"
#include "SyntaxError.h"

class ValidationChecker
{
public:
    ValidationChecker(const std::string& expression);
    void checkExpression();
    int isOperator(char s);
private:
    std::string _expression;
};

#endif // VALIDATIONCHECKER_H
