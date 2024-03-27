

#ifndef LAB1_OOP_CIRCLE_H
#define LAB1_OOP_CIRCLE_H
#include "figures.h"

class Circle: public Figures {
private:
    Point centerCoordinate;
    double radius;
public:
    Circle(std::string n, Point center, double r);
    void showParams() override;
    void showPerimeter() override;
    double findPerimeter() override;
};


#endif //LAB1_OOP_CIRCLE_H
