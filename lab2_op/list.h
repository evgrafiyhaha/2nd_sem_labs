#ifndef LIST_H
#define LIST_H

#include <cstdio>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_LENGHT 100

struct fileLine {
    int year;
    char region[LINE_MAX_LENGHT];
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
void pushEnd(List* list, fileLine line);


#endif // LIST_H
