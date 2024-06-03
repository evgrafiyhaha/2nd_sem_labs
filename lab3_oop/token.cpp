#include "token.h"

Token::Token(std::string str) {
    value = str;
    type = _Operand;
}

Token::Token(char op) {
    value = op;
    if (op == '(' || op == ')') {
        type = _Parenthesis;
    } else {
        type = _Operator;
    }
}

std::string Token::getValue() {
    return value;
}

Type Token::getType() {
    return type;
}
