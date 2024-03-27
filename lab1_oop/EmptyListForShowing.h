#ifndef LAB1_OOP_EMPTYLISTFORSHOWING_H
#define LAB1_OOP_EMPTYLISTFORSHOWING_H

#include <stdexcept>
#include <string>

#define EMPTY_LIST_FOR_SHOWING "The list of figures is empty. There is nothing to show"

class EmptyListForShowing : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForShowing(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB1_OOP_EMPTYLISTFORSHOWING_H
