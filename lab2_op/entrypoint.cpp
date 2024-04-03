#include "entrypoint.h"

void doOperation(Operation operation, AppContext* context, AppParams* params) {
    switch(operation) {
    case Initialization:
        initialize(context);
        break;
    case Loading:
        load(context);
        break;
    case CopyFileName:
        copyFileName(context, params->fileName);
        break;
    case CopyRegion:
        copyRegion(context,params->region);
        break;
    case CopyIndex:
        copyIndex(context,params->column);
        break;
    case Calculation:
        calculate(context);
        break;
    }
}
