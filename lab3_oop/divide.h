#ifndef DIVIDE_H
#define DIVIDE_H

#include "operator.h"
#include "MathError.h"

class Divide: public Operator
{
public:
    double execute(double left, double right) override;
    int getPriority() override;
};

#endif // DIVIDE_H
