#include "logic.h"

void initialize(AppContext* context) {
    context->errorData = NoErrors;
    context->max = DEFAULT_METRICS_VALUE;
    context->min = DEFAULT_METRICS_VALUE;
    context->median = DEFAULT_METRICS_VALUE;
}

void copyFileName(AppContext* context,char* fileName) {
    strcpy(context->fileName,fileName);
}

void copyRegion(AppContext* context, char* region) {
    strcpy(context->region,region);
}

void copyIndex(AppContext* context, char* column) {
    strcpy(context->column,column);
}

void load(AppContext* context) {
    FILE *file;
    file = fopen(context->fileName, "r");

    if (file) {
        char* fline = (char*)malloc(LINE_MAX_LENGHT);
        readline(file, fline);
        free(fline);

        char* line = (char*)malloc(LINE_MAX_LENGHT);
        int successRead = readline(file, line);
        fileLine firstLine;
        int numberOfLines = 0;
        int numberOfErrorLines = 0;
        int numberOfSuccessLines = 0;
        if (addLineToStruct(line, &firstLine)) {
            numberOfSuccessLines++;
        } else {
            numberOfErrorLines++;
        }
        numberOfLines++;
        free(line);

        List* list = init(firstLine);
        while (!feof(file)) {
            fileLine currentLine;
            char* line = (char*)malloc(LINE_MAX_LENGHT);
            successRead += readline(file, line);
            if (addLineToStruct(line, &currentLine)) {
                numberOfSuccessLines++;
                pushEnd(list, currentLine);
            } else {
                numberOfErrorLines++;
            }
            numberOfLines++;
            free(line);
        }

        context->table = list;
        context->numberOfErrorLines = numberOfErrorLines;
        context->numberOfLines = numberOfLines;
        context->numberOfSuccessLines = numberOfSuccessLines;

        fclose(file);
    } else {
        context->errorData = FileError;
    }
}

void calculate(AppContext* context) {
    int doCalculate = 1;
    if (!isInt(context->column) ||(isInt(context->column) && (stringToInt(context->column) > 7 || stringToInt(context->column) < 3))){
        doCalculate = 0;
        context->errorData = ColumnError;
    }
    if (doCalculate) {
        int counter = countRegionAppear(context->table, context->region);
        if (!counter) {
            context->errorData = RegionError;
        } else {
            double min = findfirstAppearance(context->table, context->region, stringToInt(context->column));
            double max = findfirstAppearance(context->table, context->region, stringToInt(context->column));
            double* columnData = (double*)malloc(sizeof(double) * counter);
            calculateData(context->table, context->region, stringToInt(context->column), &min, &max, columnData);
            double median = findMedian(columnData, counter);
            free(columnData);
            context->median = median;
            context->max = max;
            context->min = min;
        }
    }
}

int readline(FILE* stream, char* str) {
    int isSuccess = 0;
    isSuccess += fgets(str, LINE_MAX_LENGHT, stream) == NULL ? 0: 1;
    int len = strlen(str);
    if (str[len - 1] == '\n')
        str[len - 1] = '\0';
    return isSuccess;
}

int addLineToStruct(char* str, fileLine* line) {
    int isSuccess = 1;
    char* token = strtok(str, ",");
    if (token != NULL && isInt(token)) {
        line->year = stringToInt(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0) {
        strcpy(line->region, token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0 && isDouble(token)) {
        line->naturalPopulationGrowth = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0 && isDouble(token)) {
        line->birthRate = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0 && isDouble(token)) {
        line->deathRate = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0 && isDouble(token)) {
        line->generalDemographicWeight = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess != 0 && isDouble(token)) {
        line->urbanisation = stringToDouble(token);
    } else {
        isSuccess = 0;
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

int countRegionAppear(List* table, char* region) {
    Node* p = table->first;
    int counter = 0;

    do {
        if (!strcmp(p->data.region, region)) {
            counter++;
        }
        p = p->next;
    } while (p != NULL);
    return counter;
}

double findfirstAppearance(List* table, char* region, int column) {
    Node* p = table->first;
    double metric = 0;

    do {
        if (strcmp(p->data.region, region) == 0) {
            metric = returnField(p, column);
        }
        p = p->next;
    } while (p != NULL);
    return metric;
}


double returnField(Node* p, int column) {
    double field = 0;
    switch(column) {
    case 3:
        field = p->data.naturalPopulationGrowth;
        break;
    case 4:
        field = p->data.birthRate;
        break;
    case 5:
        field = p->data.deathRate;
        break;
    case 6:
        field = p->data.generalDemographicWeight;
        break;
    case 7:
        field = p->data.urbanisation;
        break;
    }
    return field;
}

void calculateData(List* table,char* region, int column, double* min, double* max, double* columnData) {
    Node* p = table->first;
    int counter = 0;

    do {
        if (strcmp(p->data.region, region) == 0) {
            double metric = returnField(p, column);
            if (metric > *max) {
                *max = metric;
            } else if (metric < *min) {
                *min = metric;
            }
            columnData[counter] = metric;
            counter++;
        }
        p = p->next;
    } while (p != NULL);
}

double findMedian(double* columnData, int counter) {
    sort(columnData, counter);
    double median;

    if (counter % 2 != 0) {
        median = columnData[counter/2];
    } else {
        median = (columnData[counter/2 - 1]+columnData[counter/2]) / 2;
    }
    return median;
}

void swap(double* x, double* y) {
    double temp = *x;
    *x = *y;
    *y = temp;
}

void sort(double arr[], int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (*(arr + i) > *(arr + j))
                swap(arr + i, arr + j);
}
