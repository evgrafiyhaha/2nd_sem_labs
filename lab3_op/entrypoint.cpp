#include "entrypoint.h"

void doOperation(Operation operation, AppContext* context, AppParams* params) {
    switch(operation) {
    case Initialization:
        initialize(context);
        break;
    case Loading:
        load(context);
        break;
    case SetFileName:
        setFileName(context, params->fileName);
        break;
    case SetRegion:
        setRegion(context,params->region);
        break;
    case SetIndex:
        setIndex(context,params->column);
        break;
    case Calculation:
        calculate(context);
        break;
    }
}
