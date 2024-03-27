#ifndef LAB1_OOP_FIGURES_H
#define LAB1_OOP_FIGURES_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <utility>
#include "cmath"
#include "FiguresException.h"
#include "Point.h"

#define _USE_MATH_DEFINES

class Figures {
protected:
    std::string name;
public:
    virtual ~Figures() = default;
    virtual double findPerimeter() = 0;
    virtual void showParams() = 0;
    virtual void showPerimeter() = 0;
};

#endif //LAB1_OOP_FIGURES_H
