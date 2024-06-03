#ifndef MATHERROR_H
#define MATHERROR_H

#include <string>

#define MATH_ERROR "Division by zero"

class MathError : public std::exception {
private:
    std::string message;

public:
    explicit MathError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // MATHERROR_H
