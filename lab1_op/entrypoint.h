#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"

enum Operation {
    Translate,
    Initialization,
    Switch
};

#define MAX_INPUT_VALUE 33

struct AppParams {
    char  inputValue[MAX_INPUT_VALUE];
    int inNumberSystem;
    int outNumberSystem;
};


void doOperation(Operation operation, AppContext* context, AppParams* params);


#endif // ENTRYPOINT_H
