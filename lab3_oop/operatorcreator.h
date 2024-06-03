#ifndef OPERATORCREATOR_H
#define OPERATORCREATOR_H

#include "operator.h"
#include "add.h"
#include "divide.h"
#include "multiply.h"
#include "substract.h"
#include <map>
#include <string>

class OperatorCreator
{
    using MethodPtr = Operator* (OperatorCreator::*)();
public:
    OperatorCreator();
    Operator* create(std::string c);
private:
    std::map<std::string,MethodPtr> operators;
    Operator* createDivision();
    Operator* createSubstraction();
    Operator* createAddition();
    Operator* createMultiplication();
    void initializeOperators();
};

#endif // OPERATORCREATOR_H
