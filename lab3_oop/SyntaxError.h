#ifndef SYNTAXERROR_H
#define SYNTAXERROR_H

#include <string>

#define SYNTAX_ERROR "Invalid Syntax"

class SyntaxError : public std::exception {
private:
    std::string message;

public:
    explicit SyntaxError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // SYNTAXERROR_H
