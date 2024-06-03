#ifndef FACADE_H
#define FACADE_H

#include <string>
#include <sstream>

#include "validationchecker.h"
#include "translator.h"
#include "calculator.h"
#include "expressiontransformer.h"

class Facade
{
public:
    static std::string calculate(const std::string& expression);
};

#endif // FACADE_H
