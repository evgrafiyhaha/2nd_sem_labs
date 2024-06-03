#ifndef ADD_H
#define ADD_H

#include "operator.h"
class Add: public Operator
{
public:
    double execute(double left, double right) override;
    int getPriority() override;
};

#endif // ADD_H
