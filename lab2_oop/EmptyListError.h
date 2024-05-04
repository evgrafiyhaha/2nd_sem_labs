#ifndef LAB2_OOP_EMPTYLISTERROR_H
#define LAB2_OOP_EMPTYLISTERROR_H

#include <stdexcept>
#include <string>

#define EMPTY_LIST_ERROR "The list is empty"

class EmptyListError : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB2_OOP_EMPTYLISTERROR_H
