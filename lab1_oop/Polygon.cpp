
#include "Polygon.h"

Polygon::Polygon(std::string n, std::vector<Point*> coordinates) {
    for (unsigned i = 0; i < coordinates.size() - 1; i++) {
        for (unsigned j = i + 1; j < coordinates.size(); j++) {
            if (coordinates[i]->getX() == coordinates[j]->getX() && coordinates[i]->getY() == coordinates[j]->getY()) {
                throw FiguresException(FIGURES_MATH_ERROR);
            }
        }
    }
    if (!isConvex(coordinates)) {
        throw FiguresException(FIGURES_MATH_ERROR);
    }
    name = std::move(n);
    for (unsigned i = 0; i < coordinates.size(); i++) {
        auto p = new Point(coordinates[i]->getX(), coordinates[i]->getY());
        coords.push_back(p);
    }
}

void Polygon::showParams() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Polygon\n";
    std::cout << "Coordinates:\n";
    for(auto & coord : coords) {
        std::cout << "(" << coord->getX() << "," << coord->getY() << ")\n";
    }
}

double Polygon::findPerimeter() {
    double perimeter = 0.0;
    unsigned numVertices = coords.size();

    for (unsigned i = 0; i < numVertices; ++i) {
        unsigned nextIndex = (i + 1) % numVertices;
        perimeter += sqrt(pow((coords[i]->getX() - coords[nextIndex]->getX()), 2) + pow((coords[i]->getY() - coords[nextIndex]->getY()), 2));
    }

    return perimeter;
}

void Polygon::showPerimeter() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Polygon\n";
    std::cout << "Perimeter: " << this->findPerimeter() << "\n";
}

double orientation(Point* a, Point* b, Point* c) {
    return (b->getX() - a->getX()) * (c->getY() - a->getY()) - (b->getY() - a->getY()) * (c->getX() - a->getX());
}

bool isConvex(std::vector<Point*> coordinates) {
    size_t numVertices = coordinates.size();
    bool orientationPositive = false;
    bool orientationNegative = false;
    for (size_t i = 0; i < numVertices; ++i) {
        double orient = orientation(coordinates[i], coordinates[(i + 1) % numVertices], coordinates[(i + 2) % numVertices]);
        if (orient > 0) {
            orientationPositive = true;
        } else if (orient < 0) {
            orientationNegative = true;
        }

        if (orientationPositive && orientationNegative) {
            return false;
        }
    }

    return true;
}