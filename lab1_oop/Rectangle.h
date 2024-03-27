

#ifndef LAB1_OOP_RECTANGLE_H
#define LAB1_OOP_RECTANGLE_H
#include "figures.h"
#include "Point.h"

class Rectangle: public Figures {
private:
    Point upperLeftCornerCoord;
    Point lowerRightCornerCoord;
public:
    Rectangle(std::string n, Point c1, Point c2);
    double findPerimeter() override;
    void showParams() override;
    void showPerimeter() override;
};


#endif //LAB1_OOP_RECTANGLE_H
