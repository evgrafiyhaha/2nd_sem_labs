#include "List.h"

template <typename T>
void List<T>::add(const T& elem) {
    Node<T>* node = new Node<T>*;
    node->data = elem;
    node->next = NULL;
    if (first == NULL) {
        first = node;
    } else {
        Node<T>* temp = first;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = node;
    }
}

template <typename T>
int List<T>::get_length() const {
    int length = 0;
    Node<T>* p = first;

    if (p == NULL)
        //throw

    do {
        length++;
        p = p->next;
    } while (p != NULL);
    return length;
}

template <typename T>
void List<T>::add_range(const List<T>& lst) {
    Node<T>* p2 = lst.first;

    while (p2 != NULL) {
        this->add(p2->data);
        p2 = p2->next;
    }
}

template <typename T>
void List<T>::add_range(T* arr, int size) {
    for(int i = 0;i < size; i++) {
        this->add(arr[i]);
    }
}

template <typename T>
void List<T>::set_elem(int index,const T& elem) {
    Node<T>* p = first;

    if (p == NULL)
        //throw
    if (this->get_length() < index) {
        //throw
    }

    for (int i = 0;i < index;i++) {
         p = p->next;
    }
    p->data = elem;
}

template <typename T>
T& List<T>::get_elem(int index) {
    Node<T>* p = first;

    if (p == NULL)
        //throw
    if (this->get_length() < index) {
        //throw
    }

    for (int i = 0;i < index;i++) {
        p = p->next;
    }
    return p->data;
}

template <typename T>
void List<T>::remove_elem(int index) {
    Node<T>* p = first;

    if (p == NULL)
        //throw
    if (this->get_length() < index) {
        //throw
    }

    for (int i = 0;i < index-1;i++) {
        p = p->next;
    }
    Node<T>* p1 = p;
    if ( p->next->next != NULL) {
        p1->next = p->next->next;
    } else {
        p1->next = NULL;
    }

    delete p->next;
}
