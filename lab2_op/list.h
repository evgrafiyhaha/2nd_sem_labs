#ifndef LIST_H
#define LIST_H

#include <cstdio>
#include <stdlib.h>
#include <string.h>

struct fileLine {
    int year;
    char region[100];
    double naturalPopulationGrowth;
    double birthRate;
    double deathRate;
    double generalDemographicWeight;
    double urbanisation;
};

struct Node {
    fileLine data;
    Node* next;
};

struct List {
    Node* first;
};

List* init(fileLine line);
void addLine(List* elem, fileLine line);
void clear(List* list);

void pushStart(List* list, fileLine line);
void pushEnd(List* list, fileLine line);
void handleLines(List* list, void(*handler)(fileLine*));
void printHandler(fileLine* line);

#endif // LIST_H
