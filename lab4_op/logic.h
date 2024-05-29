#ifndef LOGIC_H
#define LOGIC_H

#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>

#include "appcontext.h"
#include "list.h"
#include "errors.h"

#define DEFAULT_METRICS_VALUE 0
#define LARGE_NUM_FOR_COMP 10000
#define SCALE_UP 1.01
#define SCALE_DOWN 0.99

void initialize(AppContext* context);
void load(AppContext* context);
void movement(AppContext* context, Coordinates coordinateForOperation, double operationParam);
void rotation(AppContext* context, Coordinates coordinateForOperation, double operationParam);
void scaling(AppContext* context, double operationParam);
void normalize(AppContext* context);


void setFileName(AppContext* context, char* fileName);
void setNormalizationFrom(AppContext* context, char* normalizationFrom);
void setNormalizationTo(AppContext* context, char* normalizationTo);

int isInt(char* str);
int isDouble(char* str);
int stringToInt(char* string);
double stringToDouble(char* string);
int readline(FILE* stream, char* str);
void fillList(FILE* file, List* list, AppContext* context, int* freeList, int* numberOfSuccessLines, int* numberOfErrorLines, int* numberOfLines);
int addLineToList(AppContext* context, char* str, List* list, int lineCounter);
double min(AppContext* context, Coordinates param);
double max(AppContext* context, Coordinates param);
Point centralPoint(AppContext* context);
double normalizeValue(AppContext* context,double value, Coordinates param);
#endif // LOGIC_H
