#ifndef LAB1_OOP_FIGURESEXCEPTION_H
#define LAB1_OOP_FIGURESEXCEPTION_H

#include <stdexcept>
#include <string>

#define FIGURES_MATH_ERROR "Figure with these parameters cant be created"
#define INVALID_MENU_OPTION "Invalid input. Please enter a number between 1 and 8."

class FiguresException : public std::exception {
private:
    std::string message;

public:
    explicit FiguresException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB1_OOP_FIGURESEXCEPTION_H
