//
// Created by Артемий Толкишевский on 23.03.2024.
//

#ifndef LAB1_OOP_FIGURES_H
#define LAB1_OOP_FIGURES_H
#include <string>
#include <stdexcept>
#include <iostream>

class Figures {
protected:
    std::string name;



public:
     Figures() = default;
     //virtual float findPerimeter();
     //virtual void showParams();
};

class Circle: public Figures {
private:

    float centerCoordinateX;
    float centerCoordinateY;
    float radius;
public:
    void showParams();
    Circle(std::string n, float x, float y, float r);
};

class Rectangle: public Figures {
private:
    float lowerLeftCornerCoordX;
    float lowerLeftCornerCoordY;
    float upperRightCornerCoordX;
    float upperRightCornerCoordY;
public:
    Rectangle(std::string n, float x1, float y1, float x2, float y2);
    void showParams();
};

class Triangle: public Figures {
private:
    float firstCoordX;
    float firstCoordY;
    float secondCoordX;
    float secondCoordY;
    float thirdCoordX;
    float thirdCoordY;
public:
    Triangle(std::string n, float x1, float y1, float x2, float y2, float x3, float y3);
    void showParams();
};






#endif //LAB1_OOP_FIGURES_H
