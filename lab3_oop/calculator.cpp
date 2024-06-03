#include "calculator.h"
#include <sstream>

std::string vectorToString(std::vector<Token>& vec) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != 0) {
            oss << " ";
        }
        oss << vec[i].getValue();
    }
    return oss.str();
}

Calculator::Calculator(std::vector<Token> exp): expression(exp) {}

std::string Calculator::calculate() {
    std::vector<Token> stackForOperands;
    std::vector<Token> stackForOperators;
    OperatorCreator operatorCreator;
    double operationResult;

    for (Token token : expression) {
        if(token.getType() == _Operand) {
            stackForOperands.push_back(token);
        } else if (token.getType() == _Operator) {
            Operator* currentOp = operatorCreator.create(token.getValue());
            if (stackForOperators.empty() || stackForOperators.back().getType() == _Parenthesis) {
                stackForOperators.push_back(token);
                delete currentOp;
            } else {
                Operator* lastOp = operatorCreator.create(stackForOperators.back().getValue());
                if (currentOp->getPriority() > lastOp->getPriority()) {
                    stackForOperators.push_back(token);
                } else {
                    operationResult = lastOp->execute(std::stod(stackForOperands[stackForOperands.size()-2].getValue().c_str()),std::stod(stackForOperands[stackForOperands.size()-1].getValue().c_str()));
                    stackForOperands.pop_back();
                    stackForOperands.pop_back();
                    stackForOperators.pop_back();
                    stackForOperators.push_back(token);
                    stackForOperands.push_back(Token(std::to_string(operationResult)));
                }
                delete currentOp;
                delete lastOp;
            }
        } else if (token.getType() == _Parenthesis) {
            if (token.getValue() == "(") {
                stackForOperators.push_back(token);
            } else {
                while (stackForOperators.back().getValue() != "(") {
                    Operator* lastOp = operatorCreator.create(stackForOperators.back().getValue());
                    operationResult = lastOp->execute(std::stod(stackForOperands[stackForOperands.size()-2].getValue().c_str()),std::stod(stackForOperands[stackForOperands.size()-1].getValue().c_str()));
                    stackForOperands.pop_back();
                    stackForOperands.pop_back();
                    stackForOperators.pop_back();
                    stackForOperands.push_back(Token(std::to_string(operationResult)));
                }
                stackForOperators.pop_back();
            }
        }
    }

    while (stackForOperands.size() != 1) {
        Operator* op = operatorCreator.create(stackForOperators.back().getValue());
        operationResult = op->execute(std::stod(stackForOperands[stackForOperands.size()-2].getValue().c_str()),std::stod(stackForOperands[stackForOperands.size()-1].getValue().c_str()));
        stackForOperands.pop_back();
        stackForOperands.pop_back();
        stackForOperators.pop_back();
        stackForOperands.push_back(Token(std::to_string(operationResult)));
        delete op;
    }
    return stackForOperands.back().getValue();

}
