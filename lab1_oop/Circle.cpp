

#include "Circle.h"

Circle::Circle(std::string n, Point center, double r): centerCoordinate(center),radius(r) {
    if (r <= 0) {
        throw FiguresException(FIGURES_MATH_ERROR);
    }
    name = std::move(n);
}
void Circle::showParams() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Circle\n";
    std::cout << "Center coordinate: (" << centerCoordinate.getX() << "," << centerCoordinate.getY() << ")\n";
    std::cout << "Radius: " << radius << "\n";
}

double Circle::findPerimeter() {
    return 2 * M_PI * radius;
}

void Circle::showPerimeter() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Circle\n";
    std::cout << "Perimeter: " << this->findPerimeter() << "\n";
}