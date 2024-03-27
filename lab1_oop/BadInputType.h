#ifndef LAB1_OOP_BADINPUTTYPE_H
#define LAB1_OOP_BADINPUTTYPE_H

#include <stdexcept>
#include <string>

class BadInputType : public std::exception {
private:
    std::string message;

public:
    explicit BadInputType(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};
#define BAD_VALUE_TYPE "Incorrect value type"

#endif //LAB1_OOP_BADINPUTTYPE_H
