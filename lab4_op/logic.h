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

void initialize(AppContext* context);
void load(AppContext* context);
void movement(AppContext* context);
void changeCoordinate(AppContext* context, int currentCoordinateOperation);
void changeDirection(AppContext* context, int direction);
void rotation(AppContext* context);
void scaling(AppContext* context);
//void calculate(AppContext* context);

void setFileName(AppContext* context, char* fileName);
void setNormalizationFrom(AppContext* context, char* normalizationFrom);
void setNormalizationTo(AppContext* context, char* normalizationTo);

int isInt(char* str);
int isDouble(char* str);
int stringToInt(char* string);
double stringToDouble(char* string);
int readline(FILE* stream, char* str);
void fillList(FILE* file, List* list, AppContext* context, int* freeList, int* numberOfSuccessLines, int* numberOfErrorLines, int* numberOfLines);
int addLineToList(char* str, List* list, int lineCounter);
#endif // LOGIC_H
