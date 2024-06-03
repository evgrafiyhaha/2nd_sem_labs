#include "expressiontransformer.h"



std::string ExpressionTransformer::addingZeros(std::string _expression) {
    std::string changedExpression = _expression;
    if (changedExpression[0] == '-') {
        changedExpression.insert(0, "0");
    }
    for (size_t i = 1;i < changedExpression.length(); i++) {
        if (changedExpression[i-1] == '(' && changedExpression[i] == '-') {
            changedExpression.insert(i, "0");
            i++;
        }
    }
    return changedExpression;
}
