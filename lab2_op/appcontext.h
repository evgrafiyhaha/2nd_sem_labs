#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "list.h"
#include "errors.h"

struct AppContext {
    double min;
    double max;
    double median;
    Errors errorData;
    int numberOfLines;
    int numberOfErrorLines;
    int numberOfSuccessLines;
    List* table;
    char fileName[100];
    char region[100];
    char column[100];
};

#endif // APPCONTEXT_H
