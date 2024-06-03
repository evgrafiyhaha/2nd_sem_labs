#include "operatorcreator.h"

OperatorCreator::OperatorCreator() {
    initializeOperators();
}

void OperatorCreator::initializeOperators() {
    operators["+"] = &OperatorCreator::createAddition;
    operators["-"] = &OperatorCreator::createSubstraction;
    operators["*"] = &OperatorCreator::createMultiplication;
    operators["/"] = &OperatorCreator::createDivision;
}


Operator* OperatorCreator::createAddition() {
    return new Add();
}

Operator* OperatorCreator::createSubstraction() {
    return new Substract();
}

Operator* OperatorCreator::createMultiplication() {
    return new Multiply();
}

Operator* OperatorCreator::createDivision() {
    return new Divide();
}

Operator* OperatorCreator::create(std::string c) {
    auto it = operators.find(c);
    if (it != operators.end()) {
        return (this->*(it->second))();
    }
    return nullptr;
}
