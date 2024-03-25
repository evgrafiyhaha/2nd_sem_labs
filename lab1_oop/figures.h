//
// Created by Артемий Толкишевский on 23.03.2024.
//

#ifndef LAB1_OOP_FIGURES_H
#define LAB1_OOP_FIGURES_H
#include <string>
#include <stdexcept>
#include <iostream>
#include "cmath"
#define _USE_MATH_DEFINES

class Figures {
protected:
    std::string name;
public:
    virtual ~Figures() = default;
    virtual double findPerimeter() = 0;
    virtual void showParams() = 0;
    virtual void showPerimeter() = 0;
};

class Circle: public Figures {
private:

    double centerCoordinateX;
    double centerCoordinateY;
    double radius;
public:
    void showParams() override;
    void showPerimeter() override;
    Circle(std::string n, double x, double y, double r);
    double findPerimeter() override;
};

class Rectangle: public Figures {
private:
    double lowerLeftCornerCoordX;
    double lowerLeftCornerCoordY;
    double upperRightCornerCoordX;
    double upperRightCornerCoordY;
public:
    Rectangle(std::string n, double x1, double y1, double x2, double y2);
    double findPerimeter() override;
    void showParams() override;
    void showPerimeter() override;
};

class Triangle: public Figures {
private:
    double firstCoordX;
    double firstCoordY;
    double secondCoordX;
    double secondCoordY;
    double thirdCoordX;
    double thirdCoordY;
public:
    Triangle(std::string n, double x1, double y1, double x2, double y2, double x3, double y3);
    void showParams() override;
    void showPerimeter() override;
    double findPerimeter() override;
};

bool comparePerimeter(Figures* f1, Figures* f2);

#endif //LAB1_OOP_FIGURES_H
