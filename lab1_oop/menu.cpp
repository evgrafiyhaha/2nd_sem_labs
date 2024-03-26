#include "menu.h"

#include <utility>


void Menu::runMenu() {
    Menu::initializeMenuOptions();
    std::string choice;
    std::vector<Figures*> figures;
    do {
        Menu::showMenu();
        std::cin >> choice;
        try {
            if (Menu::menuOptions.find(choice) != Menu::menuOptions.end()) {
                Menu::menuOptions[choice](figures);
            } else if (choice == "8"){
                ;
            } else {
                std::cerr << "Invalid input. Please enter a number between 1 and 8.\n";
            }
        } catch (const BadInputType& e) {
            std::cerr << e.what() << "\n";
        } catch (const FiguresException& e) {
            std::cerr << e.what() << "\n";
        } catch (const BadFigureName& e) {
            std::cerr << e.what() << "\n";
        } catch (const EmptyListForShowing& e) {
            std::cerr << e.what() << "\n";
        } catch (const EmptyListForDeletion& e) {
            std::cerr << e.what() << "\n";
        } catch (const EmptyListForSorting& e) {
            std::cerr << e.what() << "\n";
        } catch (const EmptyListForSumming& e) {
            std::cerr << e.what() << "\n";
        } catch (const BadIndexForDeletion& e) {
            std::cerr << e.what() << "\n";
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
    std::cout << "Choose a figure you want to add:\n";
    std::cin >> choice;
    if (Menu::figuresOptions.find(choice) != Menu::figuresOptions.end()) {
        Menu::figuresOptions[choice](list);
        std::cout << "Figure added successfully!\n";
    } else {
        throw BadFigureName("There is no such figure");
    }
}

void Menu::addTriangle(std::vector<Figures*> &list) {
    std::string name;
    //std::pair<double,double> alexander;
    std::cout << "Enter a name for your figure\n";
    std::cin >> name;
    std::cout << "Enter parameters for your figure(coordinates of three points)\n";
    double firstCoordX = getValue();
    double firstCoordY = getValue();
    double secondCoordX = getValue();
    double secondCoordY = getValue();
    double thirdCoordX = getValue();
    double thirdCoordY = getValue();
    list.push_back(new Triangle(name, firstCoordX, firstCoordY, secondCoordX, secondCoordY, thirdCoordX, thirdCoordY));
}

void Menu::addCircle(std::vector<Figures*> &list) {
    std::string name;
    std::cout << "Enter a name for your figure\n";
    std::cin >> name;
    std::cout << "Enter parameters for your figure(coordinates of centre and radius)\n";
    double centerCoordinateX = getValue();
    double centerCoordinateY = getValue();
    double radius = getValue();
    list.push_back(new Circle(name, centerCoordinateX, centerCoordinateY, radius));
}

void Menu::addRectangle(std::vector<Figures*> &list) {
    std::string name;
    std::cout << "Enter a name for your figure\n";
    std::cin >> name;
    std::cout << "Enter parameters for your figure(coordinates of two points)\n";
    double lowerLeftCornerCoordX = getValue();
    double lowerLeftCornerCoordY = getValue();
    double upperRightCornerCoordX = getValue();
    double upperRightCornerCoordY = getValue();
    list.push_back(new Rectangle(name, lowerLeftCornerCoordX, lowerLeftCornerCoordY, upperRightCornerCoordX, upperRightCornerCoordY));
}

void Menu::showFigures(std::vector<Figures*> &list) {
    unsigned counter = 1;
    if (list.empty()) {
        throw EmptyListForShowing("The list of figures is empty. There is nothing to show");
    }
    for (const auto& figure:list) {
        std::cout << counter << ". ";
        figure->showParams();
        counter++;
    }
}

void Menu::showPerimeters(std::vector<Figures*> &list) {
    unsigned counter = 1;
    if (list.empty()) {
        throw EmptyListForShowing("The list of figures is empty. There is nothing to show");
    }
    for (const auto& figure:list) {
        std::cout << counter << ". ";
        figure->showPerimeter();
        counter++;
    }
}

void Menu::printSumOfPerimeters(std::vector<Figures*> &list) {
    if (list.empty()) {
        throw EmptyListForSumming("The list of figures is empty. There is nothing to sum");
    }
    double sum = 0;
    for (const auto& figure:list) {
        sum += figure->findPerimeter();
    }
    std::cout << "Sum of Perimeters: " << sum << "\n";
}

void Menu::sortFiguresByPerimeter(std::vector<Figures*> &list) {
    if (list.empty()) {
        throw EmptyListForSorting("The list of figures is empty. There is nothing to sort");
    }
    std::sort(list.begin(), list.end(), comparePerimeter);
    std::cout << "Figures have been sorted!: " << "\n";
}

bool comparePerimeter(Figures* f1, Figures* f2) {
    return (f1->findPerimeter() < f2->findPerimeter());
}

void Menu::deleteFigureByIndex(std::vector<Figures*> &list) {
    if (list.empty()) {
        throw EmptyListForDeletion("The list of figures is empty.There is nothing to delete");
    }
    std::cout << "Enter an index of a figure you want to delete(from 0): " << "\n";
    int index = getIntValue();
    if (index < 0 || index > list.size()) {
        throw BadIndexForDeletion("There is no such index");
    }
    delete list[index];
    list.erase(list.begin() + index);
    std::cout <<"Figure has been deleted!\n";
}

void Menu::deleteFiguresByPerimeter(std::vector<Figures*> &list) {
    if (list.empty()) {
        throw EmptyListForDeletion("The list of figures is empty.There is nothing to delete");
    }
    std::cout << "Enter a value to delete figures with larger perimeters: " << "\n";
    double enteredValue = getValue();
    for (unsigned i = 0;i < list.size(); i++) {
        if (list[i]->findPerimeter() > enteredValue) {
            delete list[i];
            list.erase(list.begin() + i);
        }
    }
    std::cout <<"Figures have been deleted!\n";
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

double getValue()
{
    double value;
    std::cin >> value;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(32767,'\n');
        throw BadInputType("Incorrect value type");
    } else {
        return value;
    }
}

int getIntValue()
{
    int value;
    std::cin >> value;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(32767,'\n');
        throw BadInputType("Incorrect value type");
    } else {
        return value;
    }
}