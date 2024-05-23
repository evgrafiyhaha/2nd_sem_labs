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
    case SetnormalizationFrom:
        setNormalizationFrom(context, params->normalizationFrom);
        break;
    case SetnormalizationTo:
        setNormalizationTo(context, params->normalizationTo);
        break;
    case Movement:
        movement(context);
        break;
    case ChangeCoordinate:
        changeCoordinate(context, params->currentCoordinateOperation);
        break;
    case ChangeDirection:
        changeDirection(context, params->direction);
        break;
    case Rotation:
        rotation(context);
        break;
    case Scaling:
        scaling(context);
        break;
    case Normalizing:
        normalize(context);
        break;
    }
}
