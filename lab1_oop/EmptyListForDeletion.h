
#ifndef LAB1_OOP_EMPTYLISTFORDELETION_H
#define LAB1_OOP_EMPTYLISTFORDELETION_H

#include <stdexcept>
#include <string>

#define EMPTY_LIST_FOR_DELETION "The list of figures is empty.There is nothing to delete"

class EmptyListForDeletion : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForDeletion(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB1_OOP_EMPTYLISTFORDELETION_H
