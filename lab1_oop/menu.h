#ifndef LAB1_OOP_MENU_H
#define LAB1_OOP_MENU_H

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <utility>
#include "figures.h"
#include "FiguresException.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "Triangle.h"
#include "Point.h"
#include "BadAmountOfVertices.h"
#include "BadFigureName.h"
#include "BadIndexForDeletion.h"
#include "BadInputType.h"
#include "EmptyListForDeletion.h"
#include "EmptyListForShowing.h"
#include "EmptyListForSorting.h"
#include "EmptyListForSumming.h"
class Menu {
private:

    using MethodPtr = void (Menu::*)();
    void callMethod(const int& methodName);
    void callFigureMethod(const int& methodName);

    int exitMenu;
    std::vector<Figures*> figures;
    std::map<int, MethodPtr> menuOptions;
    std::map<int, MethodPtr> figuresOptions;

    void showMenu();
    void addFigure();
    void showFigures();
    void showPerimeters();
    void printSumOfPerimeters();
    void sortFiguresByPerimeter();
    void deleteFigureByIndex();
    void deleteFiguresByPerimeter();
    void initializeMenuOptions();
    void initializeFiguresOptions();
    void exitMenuReal();

    void addTriangle();
    void addCircle();
    void addRectangle();
    void addPolygon();

    Circle* getCircle();
    Triangle* getTriangle();
    Rectangle* getRectangle();
    Polygon* getPolygon();

    template<typename T>
    T getValue();
    static bool comparePerimeter(Figures* f1, Figures* f2);

public:
    void runMenu();
};



#endif //LAB1_OOP_MENU_H
