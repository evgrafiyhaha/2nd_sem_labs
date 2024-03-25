#include "figures.h"
#include <utility>

Circle::Circle(std::string n, double x, double y, double r) {
    if (r <= 0) {
        //throw
    }
    name = std::move(n);
    centerCoordinateX = x;
    centerCoordinateY = y;
    radius = r;
}

Rectangle::Rectangle(std::string n, double x1, double y1, double x2, double y2) {
    if (x1 == x2 || y1 == y2) {
        //throw
    }
    name = std::move(n);
    lowerLeftCornerCoordX = x1;
    lowerLeftCornerCoordY = y1;
    upperRightCornerCoordX = x2;
    upperRightCornerCoordY = y2;
}

Triangle::Triangle(std::string n, double x1, double y1, double x2, double y2, double x3, double y3) {
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
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Circle\n";
    std::cout << "Center coordinate: (" << centerCoordinateX << "," << centerCoordinateY << ")\n";
    std::cout << "Radius: " << radius << "\n";
}

void Rectangle::showParams() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Rectangle\n";
    std::cout << "Lower left corner coordinate: (" << lowerLeftCornerCoordX << "," << lowerLeftCornerCoordY << ")\n";
    std::cout << "Upper right corner coordinate: (" << upperRightCornerCoordX << "," << upperRightCornerCoordY << ")\n";
}

void Triangle::showParams() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Triangle\n";
    std::cout << "First point coordinate: (" << firstCoordX << "," << firstCoordY << ")\n";
    std::cout << "Second point coordinate: (" << secondCoordX << "," << secondCoordY << ")\n";
    std::cout << "Third point coordinate: (" << thirdCoordX << "," << thirdCoordY << ")\n";
}

double Rectangle::findPerimeter() {
    return 2*(fabs(lowerLeftCornerCoordY - upperRightCornerCoordY) + fabs(lowerLeftCornerCoordX - upperRightCornerCoordX));
}

double Triangle::findPerimeter() {
    double firstLine = sqrt(pow((firstCoordX - secondCoordX), 2) + pow((firstCoordY - secondCoordY), 2));
    double secondLine = sqrt(pow((firstCoordX - thirdCoordX), 2) + pow((firstCoordY - thirdCoordY), 2));
    double thirdLine = sqrt(pow((secondCoordX - thirdCoordX), 2) + pow((secondCoordY - thirdCoordY), 2));
    return firstLine + secondLine + thirdLine;
}

double Circle::findPerimeter() {
    return 2 * M_PI * radius;
}

void Circle::showPerimeter() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Circle\n";
    std::cout << "Perimeter: " << this->findPerimeter() << "\n";
}

void Rectangle::showPerimeter() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Rectangle\n";
    std::cout << "Perimeter: " << this->findPerimeter() << "\n";
}

void Triangle::showPerimeter() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Triangle\n";
    std::cout << "Perimeter: " << this->findPerimeter() << "\n";
}