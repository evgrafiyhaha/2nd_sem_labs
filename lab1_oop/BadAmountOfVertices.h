
#ifndef LAB1_OOP_BADAMOUNTOFVERTICES_H
#define LAB1_OOP_BADAMOUNTOFVERTICES_H

#include <stdexcept>
#include <string>

#define BAD_AMOUNT_OF_VERTICES "Polygon cant have that amount of vertices"

class BadAmountOfVertices : public std::exception {
private:
    std::string message;

public:
    explicit BadAmountOfVertices(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB1_OOP_BADAMOUNTOFVERTICES_H
