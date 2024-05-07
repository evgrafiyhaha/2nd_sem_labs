#include "logic.h"

void initialize(AppContext* context) {
    context->errorData = NoErrors;
    context->numberOfErrorLines = DEFAULT_METRICS_VALUE;
    context->numberOfSuccessLines = DEFAULT_METRICS_VALUE;
    context->numberOfLines = DEFAULT_METRICS_VALUE;
    strcpy(context->fileName,"");
    context->coordinates = NULL;
    context->normalizationFrom = DEFAULT_METRICS_VALUE;
    context->normalizationTo = DEFAULT_METRICS_VALUE;
    context->currentCoordinateOperation = DEFAULT_METRICS_VALUE;
    context->direction = DEFAULT_METRICS_VALUE;
}

void setFileName(AppContext* context, char* fileName) {
    strcpy(context->fileName, fileName);
    context->numberOfErrorLines = DEFAULT_METRICS_VALUE;
    context->numberOfSuccessLines = DEFAULT_METRICS_VALUE;
    context->numberOfLines = DEFAULT_METRICS_VALUE;
}


void setNormalizationFrom(AppContext* context, char* normalizationFrom) {
    if (isDouble(normalizationFrom)) {
        context->normalizationFrom = stringToDouble(normalizationFrom);
    } else {
        context->errorData = NormalizationError;
    }
}


void setNormalizationTo(AppContext* context, char* normalizationTo) {
    if (isDouble(normalizationTo)) {
        context->normalizationTo = stringToDouble(normalizationTo);
    } else {
        context->errorData = NormalizationError;
    }
}

void changeDirection(AppContext* context, int direction) {
    context->direction = direction;
}

void changeCoordinate(AppContext* context, int currentCoordinateOperation) {
    context->currentCoordinateOperation = currentCoordinateOperation;
}

void movement(AppContext* context) {
    if (strcmp(context->fileName,"")) {
        if (context->coordinates != NULL ) {
            Node* current = context->coordinates->first;
            while (current) {
                switch (context->currentCoordinateOperation) {
                case 1:
                    current->data.x+=context->direction;
                    break;
                case 2:
                    current->data.y+=context->direction;
                    break;
                case 3:
                    current->data.z+=context->direction;
                    break;
                default:
                    break;
                }
                current = current->next;
            }
        } else {
            context->errorData = EmptyListError;
        }
    } else {
        context->errorData = EmptyFileNameError;
    }
}

void rotation(AppContext* context) {
    if (strcmp(context->fileName,"")) {
        if (context->coordinates != NULL ) {
            double angle = (double)context->direction / 10;
            Node* current = context->coordinates->first;
            while (current) {
                double x = current->data.x;
                double y = current->data.y;
                double z = current->data.z;

                switch (context->currentCoordinateOperation) {
                case 1:
                    current->data.y = y * cos(angle) - z * sin(angle);
                    current->data.z = y * sin(angle) + z * cos(angle);
                    break;
                case 2:
                    current->data.x = x * cos(angle) + z * sin(angle);
                    current->data.z = -x * sin(angle) + z * cos(angle);
                    break;
                case 3:
                    current->data.x = x * cos(angle) - y * sin(angle);
                    current->data.y = x * sin(angle) + y * cos(angle);
                    break;
                default:
                    break;
                }
                current = current->next;
            }
        } else {
            context->errorData = EmptyListError;
        }
    } else {
        context->errorData = EmptyFileNameError;
    }
}

void scaling(AppContext* context) {
    if (strcmp(context->fileName,"")) {
        if (context->coordinates != NULL ) {
            double scale;
            if (context->direction == 1) {
                scale = 0.99;
            } else {
                scale = 1.01;
            }
            Node* current = context->coordinates->first;
            while (current) {
                current->data.x*=scale;
                current->data.y*=scale;
                current->data.z*=scale;
                current = current->next;
            }
        } else {
            context->errorData = EmptyListError;
        }
    } else {
        context->errorData = EmptyFileNameError;
    }
}

void load(AppContext* context) {
    if (!strcmp(context->fileName, "")) {
        context->errorData = EmptyFileNameError;
    } else {
        FILE *file;
        file = fopen(context->fileName, "r");

        if (file) {
            List* list = (List*) malloc(sizeof(List));;
            list->first = NULL;
            int numberOfLines = 0;
            int numberOfErrorLines = 0;
            int numberOfSuccessLines = 0;
            int freeList = 0;
            fillList(file, list, context, &freeList, &numberOfSuccessLines, &numberOfErrorLines, &numberOfLines);
            if (!freeList) {
                context->coordinates = list;
                context->numberOfErrorLines = numberOfErrorLines;
                context->numberOfLines = numberOfLines;
                context->numberOfSuccessLines = numberOfSuccessLines;
                context->errorData = NoErrors;
            } else {
                deleteList(list);
            }
        } else {
            context->errorData = FileError;
        }
    }
}

void fillList(FILE* file, List* list, AppContext* context, int* freeList, int* numberOfSuccessLines, int* numberOfErrorLines, int* numberOfLines) {

    while (!feof(file)) {
        char* line = (char*)malloc(LINE_MAX_LENGHT);
        if (line == NULL) {
            context->errorData = MemoryAllocationError;
            *freeList = 1;
            break;
        } else {
            int successRead = readline(file, line);
            if (successRead && addLineToList(line, list, *numberOfLines)) {
                *numberOfSuccessLines+=1;
            } else {
                *numberOfErrorLines+=1;
            }
            *numberOfLines+=1;
            free(line);
        }
    }
}

int addLineToList(char* str, List* list, int lineCounter) {
    int isSuccess = 1;
    int xCounter = 0;
    char* token = strtok(str, ",");
    while(token) {
        if (isDouble(token)) {
            Point point;
            point.x = xCounter;
            point.y = lineCounter;
            point.z = stringToDouble(token);
            pushEnd(list,point);
        } else {
            isSuccess = 0;
        }
        xCounter++;
        token = strtok(NULL, ",");
    }
    return isSuccess;
}

int isInt(char* str) {
    char* endptr;
    int isInt = 0;
    strtol(str, &endptr, 10);

    if (*endptr == '\0') {
        isInt = 1;
    }
    return isInt;
}

int isDouble(char* str) {
    char* endptr;
    int isDouble = 0;
    strtod(str, &endptr);

    if (*endptr == '\0') {
        isDouble = 1;
    }

    return isDouble;
}

int stringToInt(char* string) {
    return atoi(string);
}

double stringToDouble(char* string) {
    return atof(string);
}

int readline(FILE* stream, char* str) {
    int isSuccess = 0;
    isSuccess += fgets(str, LINE_MAX_LENGHT, stream) == NULL ? 0: 1;
    int len = strlen(str);
    if (str[len - 1] == '\n')
        str[len - 1] = '\0';
    return isSuccess;
}