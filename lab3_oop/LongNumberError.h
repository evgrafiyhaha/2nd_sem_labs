#ifndef LONGNUMBERERROR_H
#define LONGNUMBERERROR_H

#include <string>

#define LONG_NUMBER_ERROR "Number is too long"

class LongNumberError : public std::exception {
private:
    std::string message;

public:
    explicit LongNumberError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // LONGNUMBERERROR_H
