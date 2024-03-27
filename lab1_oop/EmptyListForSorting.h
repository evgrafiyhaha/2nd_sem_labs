
#ifndef LAB1_OOP_EMPTYLISTFORSORTING_H
#define LAB1_OOP_EMPTYLISTFORSORTING_H

#include <stdexcept>
#include <string>

#define EMPTY_LIST_FOR_SORTING "The list of figures is empty. There is nothing to sort"

class EmptyListForSorting : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForSorting(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB1_OOP_EMPTYLISTFORSORTING_H
