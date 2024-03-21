#include "entrypoint.h"

void doOperation(Operation operation, AppContext* context, AppParams* params) {
    switch(operation) {
    case Translate:
        doTranslate(context, params->inputValue, params->inNumberSystem, params->outNumberSystem);
        break;
    case Initialization:
        initialize(context);
        break;
    case Switch:
        doSwitch(context,params->inputValue, params->inNumberSystem, params->outNumberSystem);
        break;
    }
}

