#ifndef LAB1_OOP_EXCEPTIONS_H
#define LAB1_OOP_EXCEPTIONS_H

#include <stdexcept>
#include <string>



class FiguresException : public std::exception {
private:
    std::string message;

public:
    explicit FiguresException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class BadInputType : public std::exception {
private:
    std::string message;

public:
    explicit BadInputType(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class BadFigureName : public std::exception {
private:
    std::string message;

public:
    explicit BadFigureName(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class EmptyListForShowing : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForShowing(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class EmptyListForDeletion : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForDeletion(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class EmptyListForSorting : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForSorting(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class EmptyListForSumming : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForSumming(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class BadIndexForDeletion : public std::exception {
private:
    std::string message;

public:
    explicit BadIndexForDeletion(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB1_OOP_EXCEPTIONS_H
