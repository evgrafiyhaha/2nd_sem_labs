#ifndef SUBSTRACT_H
#define SUBSTRACT_H

#include "operator.h"

class Substract: public Operator
{
public:
    double execute(double left, double right) override;
    int getPriority() override;
};

#endif // SUBSTRACT_H
