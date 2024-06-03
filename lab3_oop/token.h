#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum Type {
    _Operator,
    _Operand,
    _Parenthesis
};

class Token
{
public:
    Token(std::string str);
    Token(char op);
    std::string getValue();
    Type getType();
private:
    std::string value;
    Type type;
};

#endif // TOKEN_H
