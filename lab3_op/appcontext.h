#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "list.h"
#include "errors.h"

struct AppContext {
    double min;
    double max;
    double median;
    Error errorData;
    int numberOfLines;
    int numberOfErrorLines;
    int numberOfSuccessLines;
    List* table;
    char fileName[LINE_MAX_LENGHT];
    char region[LINE_MAX_LENGHT];
    char column[LINE_MAX_LENGHT];
};

#endif // APPCONTEXT_H
