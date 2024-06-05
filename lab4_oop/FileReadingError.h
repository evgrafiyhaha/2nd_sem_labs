#ifndef FILEREADINGERROR_H
#define FILEREADINGERROR_H

#include <string>

#define FILE_ERROR "Unable to open file"
#define NOT_NUMBER_ERROR "Cannot convert to double"
#define NORMALIZATION_ERROR "Invalid Normalization data"

class FileReadingError : public std::exception {
private:
    std::string message;

public:
    explicit FileReadingError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // FILEREADINGERROR_H
