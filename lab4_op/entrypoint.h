#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"

enum Operation {
    Initialization,
    Loading,
    SetFileName,
    SetnormalizationFrom,
    SetnormalizationTo,
    Movement,
    ChangeCoordinate,
    ChangeDirection,
    Rotation,
    Scaling
};

struct AppParams {
    char fileName[LINE_MAX_LENGHT];
    char normalizationFrom[LINE_MAX_LENGHT];
    char normalizationTo[LINE_MAX_LENGHT];
    int currentCoordinateOperation = 0;
    int direction = 0;
};

void doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
