#include "validationchecker.h"

ValidationChecker::ValidationChecker(const std::string& expression): _expression(expression) {}

int ValidationChecker::isOperator(char s) {
    int isOperator = 0;
    for (auto c: OPERATORS) {
        if (s == c) {
            isOperator = 1;
            break;
        }
    }
    return isOperator;
}

void ValidationChecker::checkExpression() {
    if (_expression.empty()) {
        throw SyntaxError(SYNTAX_ERROR);
    }
    //addingZeros();

    int openedParenthesis = 0;
    bool lastWasOperator = true;
    bool lastWasPoint = true;
    bool lastWasOpenedParenthesis = false;
    bool lastWasClosedParenthesis = false;

    for (auto s : _expression) {
        if (s == '(') {
            if (!lastWasOperator && !lastWasOpenedParenthesis && !lastWasClosedParenthesis) {
                throw SyntaxError(SYNTAX_ERROR);
            }
            openedParenthesis++;
            lastWasOperator = false;
            lastWasPoint = false;
            lastWasOpenedParenthesis = true;
            lastWasClosedParenthesis = false;
        } else if (s == ')') {
            if (lastWasOperator || openedParenthesis == 0 || lastWasPoint) {
                throw SyntaxError(SYNTAX_ERROR);
            }
            openedParenthesis--;
            lastWasOperator = false;
            lastWasPoint = false;
            lastWasClosedParenthesis = true;
            lastWasOpenedParenthesis = false;
        } else if (isOperator(s)) {
            if (lastWasOperator || lastWasPoint || lastWasOpenedParenthesis) {
                throw SyntaxError(SYNTAX_ERROR);
            }
            lastWasPoint = false;
            lastWasOperator = true;
            lastWasOpenedParenthesis = false;
            lastWasClosedParenthesis = false;
        } else if (isdigit(s)) {
            lastWasOperator = false;
            lastWasPoint = false;
            lastWasOpenedParenthesis = false;
            lastWasClosedParenthesis = false;
        } else if (s == '.') {
            if (lastWasOperator || lastWasPoint || lastWasOpenedParenthesis || lastWasClosedParenthesis) {
                throw SyntaxError(SYNTAX_ERROR);
            }
            lastWasPoint = true;
            lastWasOperator = false;
            lastWasOpenedParenthesis = false;
            lastWasClosedParenthesis = false;
        }
    }

    if (openedParenthesis != 0 || lastWasOperator || lastWasPoint) {
        throw SyntaxError(SYNTAX_ERROR);
    }
}
