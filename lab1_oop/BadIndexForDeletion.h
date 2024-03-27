
#ifndef LAB1_OOP_BADINDEXFORDELETION_H
#define LAB1_OOP_BADINDEXFORDELETION_H

#include <stdexcept>
#include <string>

#define BAD_LIST_INDEX "There is no such index"

class BadIndexForDeletion : public std::exception {
private:
    std::string message;

public:
    explicit BadIndexForDeletion(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB1_OOP_BADINDEXFORDELETION_H
