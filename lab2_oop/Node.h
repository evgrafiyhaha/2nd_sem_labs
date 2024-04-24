#ifndef LAB2_OOP_NODE_H
#define LAB2_OOP_NODE_H
#include "Data.h"

template <typename T>
struct Node {
    Data<T> data;
    Node* next;
};

#endif //LAB2_OOP_NODE_H
