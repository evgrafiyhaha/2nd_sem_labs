#ifndef LAB2_OOP_INDEXERROR_H
#define LAB2_OOP_INDEXERROR_H

#include <stdexcept>
#include <string>

#define INDEX_ERROR "Invalid Index"

class IndexError : public std::exception {
private:
    std::string message;

public:
    explicit IndexError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB2_OOP_INDEXERROR_H
