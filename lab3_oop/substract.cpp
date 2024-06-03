#include "substract.h"

double Substract::execute(double left, double right) {
    return left - right;
}

int Substract::getPriority() {
    return 1;
}
