#include "menu.h"


void Menu::runMenu(){
    std::string choice;
    do {
        Menu::showMenu();
        std::cin >> choice;
        if (choice.length() != 1) {
            printf("Error reading input. Please input number in range 1-7\n");
            continue;
        }
        if (choice.length() == 1) {
            switch (choice[0]) {
                case '1':
                    ;
                    break;
                case '2':
                    ;
                    break;
                case '3':
                    ;
                    break;
                case '4':
                    ;
                    break;
                case '5':
                    ;
                    break;
                case '6':
                    ;
                    break;
                case '7':
                    ;
                    break;
                default:
                    printf("Invalid choice. Try again.\n");
            }
        } else {
            printf("Invalid input. Please enter a single character.\n");
        }

    } while (choice[0] != '7' && choice.length() == 1);
}

void Menu::showMenu() {
    std::cout << "Menu:\n"
                 "1.Add the selected shape to the general collection of shapes\n"
                 "2.Output a list of shapes with the shape type and its parameters\n"
                 "3.Output a list of shapes with the type of shape and its perimeter\n"
                 "4.Output the sum of the perimeters of all shapes\n"
                 "5.Sort the shapes by their perimeters\n"
                 "6.Delete a shape from the collection by its number\n"
                 "7.Delete shapes whose perimeters are larger than your number\n";
}