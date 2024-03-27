
#ifndef LAB1_OOP_EMPTYLISTFORSUMMING_H
#define LAB1_OOP_EMPTYLISTFORSUMMING_H

#include <stdexcept>
#include <string>

#define EMPTY_LIST_FOR_SUMMING "The list of figures is empty. There is nothing to sum"

class EmptyListForSumming : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForSumming(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB1_OOP_EMPTYLISTFORSUMMING_H
