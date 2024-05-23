#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "list.h"
#include "errors.h"

struct AppContext {
    Error errorData;
    int numberOfLines;
    int numberOfErrorLines;
    int numberOfSuccessLines;
    List* coordinates;
    char fileName[LINE_MAX_LENGHT];
    double normalizationFrom;
    double normalizationTo;
    int cellSize = 20;
    int currentCoordinateOperation;
    int direction;
    Point centerPoint;
    int lineLength;
};
#endif // APPCONTEXT_H
