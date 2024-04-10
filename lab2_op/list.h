#ifndef LIST_H
#define LIST_H

#include <cstdio>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_LENGHT 100

struct FileLine {
    int year;
    char region[LINE_MAX_LENGHT];
    double naturalPopulationGrowth;
    double birthRate;
    double deathRate;
    double generalDemographicWeight;
    double urbanisation;
};

struct Node {
    FileLine data;
    Node* next;
};

struct List {
    Node* first;
};

List* init(FileLine line);
void pushEnd(List* list, FileLine line);
void deleteList(List* list);


#endif // LIST_H
