//
// Created by Артемий Толкишевский on 27.03.2024.
//

#ifndef LAB1_OOP_POLYGON_H
#define LAB1_OOP_POLYGON_H
#include "figures.h"
#include "Point.h"

class Polygon: public Figures {
private:
    std::vector<Point*> coords;
public:
    Polygon(std::string n, std::vector<Point*> coordinates);
    void showParams() override;
    void showPerimeter() override;
    double findPerimeter() override;
};

double orientation(Point* a, Point* b, Point* c);
bool isConvex(std::vector<Point*> coordinates);


#endif //LAB1_OOP_POLYGON_H
