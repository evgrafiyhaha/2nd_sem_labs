#ifndef LAB2_OOP_LIST_H
#define LAB2_OOP_LIST_H

#include <iostream>
#include <vector>
#include "Node.h"
#include "Iterator.h"

#include "EmptyListError.h"
#include "IndexError.h"
#include "InvalidSize.h"

template <typename T>
class List {
    friend class Iterator<T>;
public:

    using iterator = Iterator<T>;

    List();
    List(const List<T>& lst);
    List(List<T>&& lst) noexcept ;
    List(std::initializer_list<T> lst);
    ~List();

    size_t get_length() const;
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
    static int compare(const T& a, const T& b);

    T& operator[](int index);
    List<T>& operator =(const List<T>& lst);

    iterator begin() const noexcept { return Iterator<T>(first, count); }
    iterator end() const noexcept { return Iterator<T>(first, count, *count); }

private:
    std::shared_ptr<Node<T>> first;
    std::shared_ptr<size_t> count;
};



template <typename T>
List<T>::List() : first(nullptr), count(std::make_shared<size_t>(0)) {}

template <typename T>
List<T>::List(const List<T>& lst) : first(nullptr), count(std::make_shared<size_t>(0)) {
    std::shared_ptr<Node<T>> current = lst.first;

    while (current != nullptr) {
        add(current->data);
        current = current->next;
    }
}

template <typename T>
List<T>::List(List<T>&& lst) noexcept : first(std::move(lst.first)), count(std::move(lst.count)) {
    lst.first = nullptr;
    lst.count = nullptr;
}

template <typename T>
List<T>::List(std::initializer_list<T> lst) : first(nullptr), count(std::make_shared<size_t>(0)) {
    for (const T& element : lst) {
        add(element);
    }
}

template <typename T>
size_t List<T>::get_length() const {
    return *count;
}

template <typename T>
T& List<T>::operator[](int index) {
    std::shared_ptr<Node<T>> p = first;

    if (p == nullptr)
        throw EmptyListError(EMPTY_LIST_ERROR);
    if (get_length() < index || index < 0) {
        throw IndexError(INDEX_ERROR);
    }

    for (int i = 0;i < index;i++) {
        p = p->next;
    }
    return p->data;
}

template <typename T>
List<T>::~List() = default;

template <typename T>
void List<T>::add(const T& elem) {
    auto node = std::make_shared<Node<T>>();
    node->data = elem;
    node->next = nullptr;
    if (first == nullptr) {
        first = node;
    } else {
        auto temp = first;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = node;
    }
    (*count)++;
}

template <typename T>
void List<T>::add_range(const List<T>& lst) {
    auto p2 = lst.first;

    while (p2 != nullptr) {
        this->add(p2->data);
        p2 = p2->next;
    }
}

template <typename T>
void List<T>::add_range(T* arr, int size) {
    if (size < 0) {
        throw InvalidSizeError(INVALID_SIZE_ERROR);
    }

    for(int i = 0;i < size; i++) {
        this->add(arr[i]);
    }
}

template <typename T>
List<T> List<T>::combine(const List<T>& lst) {
    List<T> result(*this);

    result.add_range(lst);

    return result;
}

template <typename T>
void List<T>::set_elem(int index,const T& elem) {
    auto p = first;

    if (p == nullptr)
        throw EmptyListError(EMPTY_LIST_ERROR);
    if (get_length() < index || index < 0) {
        throw IndexError(INDEX_ERROR);
    }

    for (int i = 0;i < index;i++) {
        p = p->next;
    }
    p->data = elem;
}

template <typename T>
T& List<T>::get_elem(int index) {
    auto p = first;

    if (p == nullptr)
        throw EmptyListError(EMPTY_LIST_ERROR);
    if (get_length() < index || index < 0) {
        throw IndexError(INDEX_ERROR);
    }

    for (int i = 0;i < index;i++) {
        p = p->next;
    }
    return p->data;
}

template <typename T>
void List<T>::remove_elem(int index) {
    auto p = first;

    if (p == nullptr)
        throw EmptyListError(EMPTY_LIST_ERROR);
    if (get_length() < index || index < 0) {
        throw IndexError(INDEX_ERROR);
    }

    for (int i = 0;i < index-1;i++) {
        p = p->next;
    }
    auto p1 = p;
    if ( p->next->next != nullptr) {
        p1->next = p->next->next;
    } else {
        p1->next = nullptr;
    }
    (*count)--;
}

template <typename T>
int List<T>::get_index(T &elem) const {
    auto p = first;
    int index = 0;
    int answer = -1;

    while (p != nullptr) {
        if (p->data == elem) {
            answer = index;
        }
        index++;
        p = p->next;
    }

    return answer;
}

template <typename T>
T* List<T>::to_array() {
    int length = this->get_length();
    T* arr = new T[length];
    auto p = first;
    int index = 0;

    do {
        arr[index++] = p->data;
        p = p->next;
    } while (p != nullptr);

    return arr;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& lst) {
    if (this == &lst)
        return *this;

    first = nullptr;
    count = std::make_shared<size_t>(0);
    auto current = lst.first;
    while (current != nullptr) {
        auto next = current->next;
        add(current->data);
        current = next;
    }
    return *this;
}

template <typename T>
void List<T>::sort(int (*comp)(const T& r1, const T& r2)) {
    if (get_length() <= 1) return;

    bool swapped;
    do {
        swapped = false;
        std::shared_ptr<Node<T>> ptr1 = first;
        std::shared_ptr<Node<T>> ptr2 = first->next;
        while (ptr2 != nullptr) {
            if (comp(ptr1->data, ptr2->data) > 0) {
                std::swap(ptr1->data, ptr2->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    } while (swapped);
}

template <typename T>
int List<T>::compare(const T& a, const T& b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

template <typename T>
std::ostream& operator <<(std::ostream& os, List<T>& lst) {
    for (int i = 0; i < lst.get_length(); i++)
        os << lst[i] << " ";

    return os;
}

#endif //LAB2_OOP_LIST_H
