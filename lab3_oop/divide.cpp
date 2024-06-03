#include "divide.h"

double Divide::execute(double left, double right) {
    if (right == 0) {
        throw MathError(MATH_ERROR);
    }
    return left / right;
}

int Divide::getPriority() {
    return 2;
}
