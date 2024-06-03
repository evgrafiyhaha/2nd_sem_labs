#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "operator.h"

class Multiply: public Operator
{
public:
    double execute(double left, double right) override;
    int getPriority() override;
};

#endif // MULTIPLY_H

