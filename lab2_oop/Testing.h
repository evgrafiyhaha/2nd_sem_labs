#ifndef LAB2_OOP_TESTING_H
#define LAB2_OOP_TESTING_H
#include "List.h"

void runTests();
template <typename T>
void additionTests(List<T> &lst);
template <typename T>
void deletionTests(List<T> &lst);
template <typename T>
void getsTests(List<T> &lst);
template <typename T>
void extraTests(List<T> &lst);
template <typename T>
void iteratorTests(List<T> &lst);

#endif //LAB2_OOP_TESTING_H
