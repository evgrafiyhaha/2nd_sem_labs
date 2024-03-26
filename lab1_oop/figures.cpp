#include "figures.h"

Circle::Circle(std::string n, double x, double y, double r) {
    if (r <= 0) {
        throw FiguresException(FIGURES_MATH_ERROR);
    }
    name = std::move(n);
    centerCoordinateX = x;
    centerCoordinateY = y;
    radius = r;
}

Rectangle::Rectangle(std::string n, double x1, double y1, double x2, double y2) {
    if (x1 == x2 || y1 == y2) {
        throw FiguresException(FIGURES_MATH_ERROR);
    }
    name = std::move(n);
    lowerLeftCornerCoordX = x1;
    lowerLeftCornerCoordY = y1;
    upperRightCornerCoordX = x2;
    upperRightCornerCoordY = y2;
}

Triangle::Triangle(std::string n, double x1, double y1, double x2, double y2, double x3, double y3) {
    double firstLine = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    double secondLine = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
    double thirdLine = sqrt(pow((x2 - x3), 2) + pow((y2 - y3), 2));
    if (firstLine >= secondLine + thirdLine || secondLine >= firstLine + thirdLine || thirdLine >= secondLine + firstLine) {
        throw FiguresException(FIGURES_MATH_ERROR);
    }
    name = std::move(n);
    firstCoordX = x1;
    firstCoordY = y1;
    secondCoordX = x2;
    secondCoordY = y2;
    thirdCoordX = x3;
    thirdCoordY = y3;
}

Polygon::Polygon(std::string n, std::vector<Point*> coordinates) {
    for (unsigned i = 0; i < coordinates.size() - 1; i++) {
        for (unsigned j = i + 1; j < coordinates.size(); j++) {
            if (coordinates[i]->x == coordinates[j]->x && coordinates[i]->y == coordinates[j]->y) {
                throw FiguresException(FIGURES_MATH_ERROR);
            }
        }
    }
    name = std::move(n);
    for (unsigned i = 0; i < coordinates.size(); i++) {
        auto* p = new Point;
        p->x = coordinates[i]->x;
        p->y = coordinates[i]->y;
        coords.push_back(p);
    }
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

void Polygon::showParams() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Polygon\n";
    std::cout << "Coordinates:\n";
    for(auto & coord : coords) {
        std::cout << "(" << coord->x << "," << coord->y << ")\n";
    }
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

double Polygon::findPerimeter() {
    double perimeter = 0.0;
    unsigned numVertices = coords.size();

    for (unsigned i = 0; i < numVertices; ++i) {
        unsigned nextIndex = (i + 1) % numVertices;
        perimeter += sqrt(pow((coords[i]->x - coords[nextIndex]->x), 2) + pow((coords[i]->y - coords[nextIndex]->y), 2));
    }

    return perimeter;
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

void Polygon::showPerimeter() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Polygon\n";
    std::cout << "Perimeter: " << this->findPerimeter() << "\n";
}