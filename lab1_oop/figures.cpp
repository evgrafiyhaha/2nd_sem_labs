#include "figures.h"

#include <utility>

Circle::Circle(std::string n, float x, float y, float r) {
    if (r <= 0) {
        //throw
    }
    name = std::move(n);
    centerCoordinateX = x;
    centerCoordinateY = y;
    radius = r;
}

Rectangle::Rectangle(std::string n, float x1, float y1, float x2, float y2) {
    if (x1 >= x2 || y1 >= y2) {
        //throw
    }
    name = std::move(n);
    lowerLeftCornerCoordX = x1;
    lowerLeftCornerCoordY = y1;
    upperRightCornerCoordX = x2;
    upperRightCornerCoordY = y2;
}

Triangle::Triangle(std::string n, float x1, float y1, float x2, float y2, float x3, float y3) {
    //написать проверерку на правильность
    name = std::move(n);
    firstCoordX = x1;
    firstCoordY = y1;
    secondCoordX = x2;
    secondCoordY = y2;
    thirdCoordX = x3;
    thirdCoordY = y3;
}

void Circle::showParams() {
    std::cout << "Name:" << name << "\n";
    std::cout << "Type: Circle\n";
    std::cout << "Center coordinate: (" << centerCoordinateX << "," << centerCoordinateY << ")\n";
    std::cout << "Radius:" << radius << "\n";
}

void Rectangle::showParams() {
    std::cout << "Name:" << name << "\n";
    std::cout << "Type: Rectangle\n";
    std::cout << "Lower left corner coordinate: (" << lowerLeftCornerCoordX << "," << lowerLeftCornerCoordY << ")\n";
    std::cout << "Upper right corner coordinate: (" << upperRightCornerCoordX << "," << upperRightCornerCoordY << ")\n";
}

void Triangle::showParams() {
    std::cout << "Name:" << name << "\n";
    std::cout << "Type: Rectangle\n";
    std::cout << "First point coordinate: (" << firstCoordX << "," << firstCoordY << ")\n";
    std::cout << "Second point coordinate: (" << secondCoordX << "," << secondCoordY << ")\n";
    std::cout << "Third point coordinate: (" << thirdCoordX << "," << thirdCoordY << ")\n";
}