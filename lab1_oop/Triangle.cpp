
#include "Triangle.h"

Triangle::Triangle(std::string n, Point c1, Point c2, Point c3): firstCoord(c1), secondCoord(c2), thirdCoord(c3) {
    double firstLine = sqrt(pow((firstCoord.getX() - secondCoord.getX()), 2) + pow((firstCoord.getY() - secondCoord.getY()), 2));
    double secondLine = sqrt(pow((firstCoord.getX() - thirdCoord.getX()), 2) + pow((firstCoord.getX() - thirdCoord.getY()), 2));
    double thirdLine = sqrt(pow((secondCoord.getX() - thirdCoord.getX()), 2) + pow((secondCoord.getY() - thirdCoord.getY()), 2));
    if (firstLine >= secondLine + thirdLine || secondLine >= firstLine + thirdLine || thirdLine >= secondLine + firstLine) {
        throw FiguresException(FIGURES_MATH_ERROR);
    }
    name = std::move(n);
}

void Triangle::showParams() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Triangle\n";
    std::cout << "First point coordinate: (" << firstCoord.getX() << "," << firstCoord.getY() << ")\n";
    std::cout << "Second point coordinate: (" << secondCoord.getX() << "," << secondCoord.getY() << ")\n";
    std::cout << "Third point coordinate: (" << thirdCoord.getX() << "," << thirdCoord.getY() << ")\n";
}

double Triangle::findPerimeter() {
    double firstLine = sqrt(pow((firstCoord.getX() - secondCoord.getX()), 2) + pow((firstCoord.getY() - secondCoord.getY()), 2));
    double secondLine = sqrt(pow((firstCoord.getX() - thirdCoord.getX()), 2) + pow((firstCoord.getY() - thirdCoord.getY()), 2));
    double thirdLine = sqrt(pow((secondCoord.getX() - thirdCoord.getX()), 2) + pow((secondCoord.getY() - thirdCoord.getY()), 2));
    return firstLine + secondLine + thirdLine;
}

void Triangle::showPerimeter() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Triangle\n";
    std::cout << "Perimeter: " << this->findPerimeter() << "\n";
}