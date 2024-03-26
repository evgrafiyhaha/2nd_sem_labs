#ifndef LAB1_OOP_MENU_H
#define LAB1_OOP_MENU_H

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <utility>
#include "figures.h"
#include "Exceptions.h"

class Menu {
public:
    static std::map<std::string, std::function<void(std::vector<Figures*>&)>> menuOptions;
    static std::map<std::string, std::function<void(std::vector<Figures*>&)>> figuresOptions;
    static void initializeMenuOptions();
    static void initializeFiguresOptions();
    static void runMenu();
    static void showMenu();
    static void addFigure(std::vector<Figures*> &list);
    static void addTriangle(std::vector<Figures*> &list);
    static void addCircle(std::vector<Figures*> &list);
    static void addRectangle(std::vector<Figures*> &list);
    static void addPolygon(std::vector<Figures*> &list);
    static void showFigures(std::vector<Figures*> &list);
    static void showPerimeters(std::vector<Figures*> &list);
    static void printSumOfPerimeters(std::vector<Figures*> &list);
    static void sortFiguresByPerimeter(std::vector<Figures*> &list);
    static void deleteFigureByIndex(std::vector<Figures*> &list);
    static void deleteFiguresByPerimeter(std::vector<Figures*> &list);
};

double getValue();
int getIntValue();

#endif //LAB1_OOP_MENU_H
