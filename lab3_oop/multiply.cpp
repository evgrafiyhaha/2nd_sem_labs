#include "multiply.h"

double Multiply::execute(double left, double right) {
    return left * right;
}

int Multiply::getPriority() {
    return 2;
}
