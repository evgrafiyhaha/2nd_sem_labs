#include "menu.h"

void Menu::runMenu() {
    exitMenu = 0;
    initializeMenuOptions();
    initializeFiguresOptions();
    int choice;
    do {
        showMenu();
        std::cin >> choice;
        try {
            callMethod(choice);
        } catch (const BadInputType &e) {
            std::cerr << e.what() << "\n";
        } catch (const FiguresException &e) {
            std::cerr << e.what() << "\n";
        } catch (const BadFigureName &e) {
            std::cerr << e.what() << "\n";
        } catch (const EmptyListForShowing &e) {
            std::cerr << e.what() << "\n";
        } catch (const EmptyListForDeletion &e) {
            std::cerr << e.what() << "\n";
        } catch (const EmptyListForSorting &e) {
            std::cerr << e.what() << "\n";
        } catch (const EmptyListForSumming &e) {
            std::cerr << e.what() << "\n";
        } catch (const BadIndexForDeletion &e) {
            std::cerr << e.what() << "\n";
        } catch (const BadAmountOfVertices &e) {
            std::cerr << e.what() << "\n";
        } catch (const std::exception &e) {
            std::cerr << INVALID_MENU_OPTION << "\n";
        }

    } while (exitMenu == 0);
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

void Menu::addFigure() {
    int choice;
    std::cout << "Choose a figure you want to add:\n"
                 "Triangle (1)\n"
                 "Circle (2)\n"
                 "Rectangle (3)\n"
                 "Polygon (4)\n";
    std::cin >> choice;
    callFigureMethod(choice);
    std::cout << "Figure added successfully!\n";
}

void Menu::addTriangle() {
    Triangle *triangle = getTriangle();
    figures.push_back(triangle);
}

Triangle *Menu::getTriangle() {
    std::string name;
    std::cout << "Enter a name for your figure:\n";
    std::cin >> name;
    std::cout << "Enter parameters for your figure(coordinates of three points):\n";
    Point firstCoordinate(getValue<double>(), getValue<double>());
    Point secondCoordinate(getValue<double>(), getValue<double>());
    Point thirdCoordinate(getValue<double>(), getValue<double>());
    return new Triangle(name, firstCoordinate, secondCoordinate, thirdCoordinate);
}

void Menu::addCircle() {
    Circle *circle = getCircle();
    figures.push_back(circle);
}

Circle *Menu::getCircle() {
    std::string name;
    std::cout << "Enter a name for your figure:\n";
    std::cin >> name;
    std::cout << "Enter parameters for your figure(coordinates of centre and radius):\n";
    Point centerCoordinate(getValue<double>(), getValue<double>());
    double radius = getValue<double>();
    return new Circle(name, centerCoordinate, radius);
}

void Menu::addRectangle() {
    Rectangle *rectangle = getRectangle();
    figures.push_back(rectangle);
}

Rectangle *Menu::getRectangle() {
    std::string name;
    std::cout << "Enter a name for your figure:\n";
    std::cin >> name;
    std::cout << "Enter parameters for your figure(coordinates of two points):\n";
    Point upperLeftCornerCoord(getValue<double>(), getValue<double>());
    Point lowerRightCornerCoord(getValue<double>(), getValue<double>());
    return new Rectangle(name, upperLeftCornerCoord, lowerRightCornerCoord);
}


void Menu::addPolygon() {
    Polygon *polygon = getPolygon();
    figures.push_back(polygon);
}

Polygon *Menu::getPolygon() {
    std::string name;
    std::cout << "Enter a name for your figure:\n";
    std::cin >> name;
    std::cout << "Enter how many vertices your figure will have:\n";
    int numVertices = getValue<int>();
    if (numVertices < 3) {
        throw BadAmountOfVertices(BAD_AMOUNT_OF_VERTICES);
    }
    std::cout << "Enter parameters for your figure:\n";
    std::vector<Point *> coordinates;
    for (int i = 0; i < numVertices; i++) {
        auto p = new Point(getValue<double>(), getValue<double>());
        coordinates.push_back(p);
    }
    return new Polygon(name, coordinates);
}

void Menu::showFigures() {
    unsigned counter = 1;
    if (figures.empty()) {
        throw EmptyListForShowing(EMPTY_LIST_FOR_SHOWING);
    }
    for (const auto &figure: figures) {
        std::cout << counter << ". ";
        figure->showParams();
        counter++;
    }
}

void Menu::showPerimeters() {
    unsigned counter = 1;
    if (figures.empty()) {
        throw EmptyListForShowing(EMPTY_LIST_FOR_SHOWING);
    }
    for (const auto &figure: figures) {
        std::cout << counter << ". ";
        figure->showPerimeter();
        counter++;
    }
}

void Menu::printSumOfPerimeters() {
    if (figures.empty()) {
        throw EmptyListForSumming(EMPTY_LIST_FOR_SUMMING);
    }
    double sum = 0;
    for (const auto &figure: figures) {
        sum += figure->findPerimeter();
    }
    std::cout << "Sum of Perimeters: " << sum << "\n";
}

void Menu::sortFiguresByPerimeter() {
    if (figures.empty()) {
        throw EmptyListForSorting(EMPTY_LIST_FOR_SORTING);
    }
    std::sort(figures.begin(), figures.end(), comparePerimeter);
    std::cout << "Figures have been sorted!: " << "\n";
}

bool Menu::comparePerimeter(Figures *f1, Figures *f2) {
    return (f1->findPerimeter() < f2->findPerimeter());
}

void Menu::deleteFigureByIndex() {
    if (figures.empty()) {
        throw EmptyListForDeletion(EMPTY_LIST_FOR_DELETION);
    }
    std::cout << "Enter an index of a figure you want to delete(from 0): " << "\n";
    int index = getValue<int>();
    if (index < 0 || index > figures.size()) {
        throw BadIndexForDeletion(BAD_LIST_INDEX);
    }
    delete figures[index];
    figures.erase(figures.begin() + index);
    std::cout << "Figure has been deleted!\n";
}

void Menu::deleteFiguresByPerimeter() {
    if (figures.empty()) {
        throw EmptyListForDeletion(EMPTY_LIST_FOR_DELETION);
    }
    std::cout << "Enter a value to delete figures with larger perimeters: " << "\n";
    double enteredValue = getValue<double>();
    for (unsigned i = 0; i < figures.size(); i++) {
        if (figures[i]->findPerimeter() > enteredValue) {
            delete figures[i];
            figures.erase(figures.begin() + i);
        }
    }
    std::cout << "Figures have been deleted!\n";
}

void Menu::exitMenuReal() {
    exitMenu = 1;
}

void Menu::callMethod(const int& methodName) {
    auto it = menuOptions.find(methodName);
    if (it != menuOptions.end()) {
        (this->*(it->second))();
    } else {
        std::cerr << "Menu option not found" << std::endl;
    }
}

void Menu::callFigureMethod(const int& methodName) {
    auto it = figuresOptions.find(methodName);
    if (it != figuresOptions.end()) {
        (this->*(it->second))();
    } else {
        throw BadFigureName(BAD_FIGURE_NAME);
    }
}

void Menu::initializeMenuOptions() {
    menuOptions[1] = &Menu::addFigure;
    menuOptions[2] = &Menu::showFigures;
    menuOptions[3] = &Menu::showPerimeters;
    menuOptions[4] = &Menu::printSumOfPerimeters;
    menuOptions[5] = &Menu::sortFiguresByPerimeter;
    menuOptions[6] = &Menu::deleteFigureByIndex;
    menuOptions[7] = &Menu::deleteFiguresByPerimeter;
    menuOptions[8] = &Menu::exitMenuReal;
}

void Menu::initializeFiguresOptions() {
    figuresOptions[1] = &Menu::addTriangle;
    figuresOptions[2] = &Menu::addCircle;
    figuresOptions[3] = &Menu::addRectangle;
    figuresOptions[4] = &Menu::addPolygon;
}

template<typename T>
T Menu::getValue() {
    T value;
    std::cin >> value;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        throw BadInputType(BAD_VALUE_TYPE);
    }
    return value;
}
