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

void initialize(AppContext* context);
void load(AppContext* context);
void copyFileName(AppContext* context,char* fileName);
void copyRegion(AppContext* context, char* region);
void copyIndex(AppContext* context, char* column);
void calculate(AppContext* context);

int readline(FILE* stream, char* str);
int addLineToStruct(char* str, fileLine* line);
int isInt(char* str);
int isDouble(char* str);
int stringToInt(char* string);
double stringToDouble(char* string);
int countRegionAppear(List* table,char* region);
double returnMetric(Node* p,int column);
double findfirstAppearance(List* table,char* region, int column);
void calculateData(List* table,char* region, int column, double* min,double* max, double* median);
#endif // LOGIC_H
