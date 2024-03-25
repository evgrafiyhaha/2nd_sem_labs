#include "menu.h"

#include <utility>


void Menu::runMenu() {
    Menu::initializeMenuOptions();
    std::string choice;
    std::vector<Figures*> figures;
    do {
        Menu::showMenu();
        std::cin >> choice;
        if (choice.length() != 1) {
            printf("Error reading input. Please input number in range 1-7\n");
            continue;
        }
        if (Menu::menuOptions.find(choice) != Menu::menuOptions.end()) {
            Menu::menuOptions[choice](figures);
        } else if (choice == "8"){
            ;
        } else {
            printf("Invalid input. Please enter a single character.\n");
        }

    } while (choice != "8");
}

void Menu::showMenu() {
    std::cout << "Menu:\n"
                 "1.Add the selected shape to the general collection of shapes\n"
                 "2.Output a list of shapes with the shape type and its parameters\n"
                 "3.Output a list of shapes with the type of shape and its perimeter\n"
                 "4.Output the sum of the perimeters of all shapes\n"
                 "5.Sort the shapes by their perimeters\n"
                 "6.Delete a shape from the collection by its number\n"
                 "7.Delete shapes whose perimeters are larger than your number\n"
                 "8.Exit\n";
}

void Menu::addFigure(std::vector<Figures*> &list) {
    Menu::initializeFiguresOptions();
    std::string choice;
    std::cout << "Chose a figure you want to add:\n";
    std::cin >> choice;
    if (Menu::figuresOptions.find(choice) != Menu::figuresOptions.end()) {
        Menu::figuresOptions[choice](list);
        std::cout << "Figure added successfully!\n";
    } else {
        std::cout << "You are invalid((\n"
                     "There is no such figure\n";
    }
}

void Menu::addTriangle(std::vector<Figures*> &list) {
    std::string name;
    //std::pair<double,double> alexander;
    double firstCoordX;
    double firstCoordY;
    double secondCoordX;
    double secondCoordY;
    double thirdCoordX;
    double thirdCoordY;
    std::cout << "Enter a name for your figure\n";
    std::cin >> name;
    std::cout << "Enter parameters for your figure(coordinates of three points)\n";
    std::cin >> firstCoordX >> firstCoordY >> secondCoordX >> secondCoordY >> thirdCoordX >> thirdCoordY;
    list.push_back(new Triangle(name, firstCoordX, firstCoordY, secondCoordX, secondCoordY, thirdCoordX, thirdCoordY));
}

void Menu::addCircle(std::vector<Figures*> &list) {
    std::string name;
    double centerCoordinateX;
    double centerCoordinateY;
    double radius;
    std::cout << "Enter a name for your figure\n";
    std::cin >> name;
    std::cout << "Enter parameters for your figure(coordinates of centre and radius)\n";
    std::cin >> centerCoordinateX >> centerCoordinateY >> radius;
    list.push_back(new Circle(name, centerCoordinateX, centerCoordinateY, radius));
}

void Menu::addRectangle(std::vector<Figures*> &list) {
    std::string name;
    double lowerLeftCornerCoordX;
    double lowerLeftCornerCoordY;
    double upperRightCornerCoordX;
    double upperRightCornerCoordY;
    std::cout << "Enter a name for your figure\n";
    std::cin >> name;
    std::cout << "Enter parameters for your figure(coordinates of two points)\n";
    std::cin >> lowerLeftCornerCoordX >> lowerLeftCornerCoordY >> upperRightCornerCoordX >> upperRightCornerCoordY;
    list.push_back(new Rectangle(name, lowerLeftCornerCoordX, lowerLeftCornerCoordY, upperRightCornerCoordX, upperRightCornerCoordY));
}

void Menu::showFigures(std::vector<Figures*> &list) {
    unsigned counter = 1;
    for (const auto& figure:list) {
        std::cout << counter << ". ";
        figure->showParams();
        counter++;
    }
}

void Menu::showPerimeters(std::vector<Figures*> &list) {
    unsigned counter = 1;
    for (const auto& figure:list) {
        std::cout << counter << ". ";
        figure->showPerimeter();
        counter++;
    }
}

void Menu::printSumOfPerimeters(std::vector<Figures*> &list) {
    double sum = 0;
    for (const auto& figure:list) {
        sum += figure->findPerimeter();
    }
    std::cout << "Sum of Perimeters: " << sum << "\n";
}

void Menu::sortFiguresByPerimeter(std::vector<Figures*> &list) {
    std::sort(list.begin(), list.end(), comparePerimeter);
    std::cout << "Figures have been sorted!: " << "\n";
}

bool comparePerimeter(Figures* f1, Figures* f2) {
    return (f1->findPerimeter() < f2->findPerimeter());
}

void Menu::deleteFigureByIndex(std::vector<Figures*> &list) {
    int index;
    std::cout << "Enter an index of a figure you want to delete(from 0): " << "\n";
    std::cin >> index;
    if (index >=0 && index < list.size()) {
        delete list[index];
        list.erase(list.begin() + index);
        std::cout <<"Figure has been deleted!\n";
    } else {
        std::cout <<"There is no such index\n";
    }
}

void Menu::deleteFiguresByPerimeter(std::vector<Figures*> &list) {
    double enteredValue;
    std::cout << "Enter an value to delete figures with larger perimeters: " << "\n";
    std::cin >> enteredValue;
    for (unsigned i = 0;i < list.size(); i++) {
        if (list[i]->findPerimeter() > enteredValue) {
            delete list[i];
            list.erase(list.begin() + i);
        }
    }
    std::cout <<"Figures has been deleted!\n";
}

std::map<std::string, std::function<void(std::vector<Figures*>&)>> Menu::menuOptions;
std::map<std::string, std::function<void(std::vector<Figures*>&)>> Menu::figuresOptions;

void Menu::initializeMenuOptions() {
    menuOptions["1"] = &Menu::addFigure;
    menuOptions["2"] = &Menu::showFigures;
    menuOptions["3"] = &Menu::showPerimeters;
    menuOptions["4"] = &Menu::printSumOfPerimeters;
    menuOptions["5"] = &Menu::sortFiguresByPerimeter;
    menuOptions["6"] = &Menu::deleteFigureByIndex;
    menuOptions["7"] = &Menu::deleteFiguresByPerimeter;
}

void Menu::initializeFiguresOptions() {
    figuresOptions["Triangle"] = &Menu::addTriangle;
    figuresOptions["Circle"] = &Menu::addCircle;
    figuresOptions["Rectangle"] = &Menu::addRectangle;
}