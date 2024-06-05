#ifndef NOFIGURESERROR_H
#define NOFIGURESERROR_H

#include <string>

#define NO_FIGURES_ERROR "No figures found"

class NoFiguresError : public std::exception {
private:
    std::string message;

public:
    explicit NoFiguresError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // NOFIGURESERROR_H
