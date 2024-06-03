#ifndef OPERATOR_H
#define OPERATOR_H

#define OPERATORS "+-/*"
#define OPERANDS "0123456789"
#define  PARETTHESIS "()"

class Operator
{
public:
    virtual double execute(double left, double right) = 0;
    virtual int getPriority() = 0;
    virtual ~Operator() = default;
};

#endif // OPERATOR_H
