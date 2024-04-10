#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include "list.h"
#include "errors.h"

#define DEFAULT_METRICS_VALUE 0

void initialize(AppContext* context);
void load(AppContext* context);
void calculate(AppContext* context);

void setFileName(AppContext* context, char* fileName);
void setRegion(AppContext* context, char* region);
void setIndex(AppContext* context, char* column);

int readline(FILE* stream, char* str);
int addLineToStruct(char* str, FileLine* line);

void calculateData(List* table,char* region, int column, double* min, double* max, double* columnData);
double findMedian(double* columnData, int counter);

int countRegionAppear(List* table, char* region);
double returnField(Node* p, int column);
double findfirstAppearance(List* table, char* region, int column);

void fillList(FILE* file, List* list, AppContext* context, int* freeList, int* numberOfSuccessLines, int* numberOfErrorLines, int* numberOfLines);
int isInt(char* str);
int isDouble(char* str);
int stringToInt(char* string);
double stringToDouble(char* string);
void swap(double *x, double *y);
void sort(double arr[], int n);
#endif // LOGIC_H
