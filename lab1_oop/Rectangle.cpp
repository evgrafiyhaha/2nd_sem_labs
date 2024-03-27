

#include "Rectangle.h"

Rectangle::Rectangle(std::string n, Point c1, Point c2): upperLeftCornerCoord(c1), lowerRightCornerCoord(c2){
    if (upperLeftCornerCoord.getX() == lowerRightCornerCoord.getX() || upperLeftCornerCoord.getY() == lowerRightCornerCoord.getY()) {
        throw FiguresException(FIGURES_MATH_ERROR);
    }
    name = std::move(n);
}

void Rectangle::showParams() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Rectangle\n";
    std::cout << "Lower left corner coordinate: (" << upperLeftCornerCoord.getX() << "," << upperLeftCornerCoord.getY() << ")\n";
    std::cout << "Upper right corner coordinate: (" << lowerRightCornerCoord.getX() << "," << lowerRightCornerCoord.getY() << ")\n";
}

double Rectangle::findPerimeter() {
    return 2*(fabs(upperLeftCornerCoord.getY() - lowerRightCornerCoord.getY()) + fabs(upperLeftCornerCoord.getX() - lowerRightCornerCoord.getX()));
}

void Rectangle::showPerimeter() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Rectangle\n";
    std::cout << "Perimeter: " << this->findPerimeter() << "\n";
}