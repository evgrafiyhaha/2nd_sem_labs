#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"

enum Operation {
    Initialization,
    Loading,
    SetFileName,
    SetRegion,
    SetIndex,
    Calculation
};

struct AppParams {
    char fileName[LINE_MAX_LENGHT];
    char region[LINE_MAX_LENGHT];
    char column[LINE_MAX_LENGHT];
};

void doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
