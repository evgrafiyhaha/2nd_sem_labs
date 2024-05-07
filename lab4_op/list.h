#ifndef LIST_H
#define LIST_H

#include <cstdio>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_LENGHT 100

struct Point {
    double x;
    double y;
    double z;
};

enum coordinates {
    none,
    X,
    Y,
    Z
};

struct Node {
    Point data;
    Node* next;
};

struct List {
    Node* first;
};

List* init(Point point);
void pushEnd(List* list, Point point);
void deleteList(List* list);



#endif // LIST_H
