#ifndef DRAWINGERROR_H
#define DRAWINGERROR_H

#include <string>

#include "NoFiguresError.h"


class DrawingError : public std::exception {
private:
    std::string message;

public:
    explicit DrawingError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // DRAWINGERROR_H
