#ifndef LAB1_OOP_EXCEPTIONS_H
#define LAB1_OOP_EXCEPTIONS_H

#include <stdexcept>
#include <string>

#define FIGURES_MATH_ERROR "Figure with these parameters cant be created"
#define INVALID_MENU_OPTION "Invalid input. Please enter a number between 1 and 8."
#define BAD_FIGURE_NAME "There is no such figure"
#define EMPTY_LIST_FOR_SHOWING "The list of figures is empty. There is nothing to show"
#define EMPTY_LIST_FOR_SUMMING "The list of figures is empty. There is nothing to sum"
#define EMPTY_LIST_FOR_SORTING "The list of figures is empty. There is nothing to sort"
#define EMPTY_LIST_FOR_DELETION "The list of figures is empty.There is nothing to delete"
#define BAD_LIST_INDEX "There is no such index"
#define BAD_VALUE_TYPE "Incorrect value type"
#define BAD_AMOUNT_OF_VERTICES "Polygon cant have that amount of vertices"

class FiguresException : public std::exception {
private:
    std::string message;

public:
    explicit FiguresException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class BadInputType : public std::exception {
private:
    std::string message;

public:
    explicit BadInputType(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class BadFigureName : public std::exception {
private:
    std::string message;

public:
    explicit BadFigureName(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class EmptyListForShowing : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForShowing(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class EmptyListForDeletion : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForDeletion(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class EmptyListForSorting : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForSorting(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class EmptyListForSumming : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForSumming(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class BadIndexForDeletion : public std::exception {
private:
    std::string message;

public:
    explicit BadIndexForDeletion(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class BadAmountOfVertices : public std::exception {
private:
    std::string message;

public:
    explicit BadAmountOfVertices(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB1_OOP_EXCEPTIONS_H
