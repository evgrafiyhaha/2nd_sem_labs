#ifndef LAB1_OOP_BADFIGURENAME_H
#define LAB1_OOP_BADFIGURENAME_H

#include <stdexcept>
#include <string>

#define BAD_FIGURE_NAME "There is no such figure"

class BadFigureName : public std::exception {
private:
    std::string message;

public:
    explicit BadFigureName(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB1_OOP_BADFIGURENAME_H
