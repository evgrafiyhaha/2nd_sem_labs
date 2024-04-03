#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"

enum Operation {
    Initialization,
    Loading,
    CopyFileName,
    CopyRegion,
    CopyIndex,
    Calculation
};

struct AppParams {
    char fileName[100];
    char region[100];
    char column[100];
};

void doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
