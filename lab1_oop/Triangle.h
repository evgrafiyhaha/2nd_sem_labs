

#ifndef LAB1_OOP_TRIANGLE_H
#define LAB1_OOP_TRIANGLE_H
#include "figures.h"
#include "Point.h"

class Triangle: public Figures {
private:
    Point firstCoord;
    Point secondCoord;
    Point thirdCoord;
public:
    Triangle(std::string n, Point c1, Point c2, Point c3);
    void showParams() override;
    void showPerimeter() override;
    double findPerimeter() override;
};


#endif //LAB1_OOP_TRIANGLE_H
