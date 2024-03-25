//
// Created by Артемий Толкишевский on 23.03.2024.
//

#ifndef LAB1_OOP_MENU_H
#define LAB1_OOP_MENU_H
#include <string>
#include <iostream>
#include "figures.h"

class Menu {
public:
    static void runMenu();
    static void showMenu();
    static void addFigure(std::vector<Figures*> &list);
    static void addTriangle(std::vector<Figures*> &list);
    static void addCircle(std::vector<Figures*> &list);
    static void addRectangle(std::vector<Figures*> &list);
    static void showFigures(std::vector<Figures*> &list);
    static void showPerimeters(std::vector<Figures*> &list);
    static void printSumOfPerimeters(std::vector<Figures*> &list);
    static void sortFiguresByPerimeter(std::vector<Figures*> &list);
    static void deleteFigureByIndex(std::vector<Figures*> &list);

};

#endif //LAB1_OOP_MENU_H
