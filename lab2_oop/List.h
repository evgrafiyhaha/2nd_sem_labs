#ifndef LAB2_OOP_LIST_H
#define LAB2_OOP_LIST_H

#include "Node.h"
#include "Iterator.h"

template <typename T>
class List {
    friend class Iterator<T, List>;
public:
    //List(const List<T>& lst) {}//написать
    //List(List<T>&& lst) {}
    //explicit List(std::initializer_list<T> lst);
    //~list();
    int get_length() const;
    void add(const T& elem);
    void add_range(const List<T>& lst);
    void add_range(T* arr, int size);
    void set_elem(int index,const T& elem);
    T& get_elem(int index);
    void remove_elem(int index);
    List<T> combine(const List<T>& lst);
    void sort(int (*comp)(const T& r1, const T& r2));
    int get_index(T &elem) const;
    T* to_array();
    T& operator[](int index);
    Iterator<T, List> *CreateIterator()
    {
        return new Iterator<T, List>(this);
    }
private:
    Node<T>* first;
};


#endif //LAB2_OOP_LIST_H
