#ifndef LAB2_OOP_ITERATOR_H
#define LAB2_OOP_ITERATOR_H
#include <iostream>
#include "Node.h"

template <typename T>
class List;

template <typename T>
class Iterator
{
    friend class List<T>;

public:
    using iterator_category = std::forward_iterator_tag;

    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

public:
    explicit Iterator(List<T> lst): first(lst.first), count(lst.count), index(0) {}

    Iterator(const Iterator& it) = default;

    bool operator ==(const Iterator& other) const {
        return index == other.index;
    }
    bool operator !=(const Iterator& other) const {
        return index != other.index;
    }
    reference operator*() {
        return getNode()->data;
    }
    const reference operator*() const {
        return getNode()->data;
    }
    pointer operator->() {
        return &(getNode()->data);
    }
    const pointer operator->() const {
        return &(getNode()->data);
    }
    operator bool() const {
        return index != std::numeric_limits<size_t>::max();
    }
    Iterator& operator++() {
        if (auto node = getNode()) {
            ++index;
        } else {
            index = std::numeric_limits<size_t>::max();
        }
        return *this;
    }
    Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    Iterator First() {
        return Iterator(first,count);
    }

    Iterator next() {
        if (auto node = getNode()) {
            ++index;
        } else {
            index = std::numeric_limits<size_t>::max();
        }
        return *this;
    }

    T value() {
        return getNode()->data;
    }

    bool is_end() {
        if (index >= *count) {
            return true;
        } else {
            return false;
        }

    }

private:
    Iterator(const std::shared_ptr<Node<T>>& f, const std::shared_ptr<size_t>& c, size_t ind = 0)
            : first(f), count(c), index(ind) {}

    std::shared_ptr<Node<T>> getNode() const {
        if (index >= *count) return nullptr;
        auto current = first;
        for (size_t i = 0; i < index; ++i)
            current = current->next;
        return current;
    }

private:
    std::shared_ptr<Node<T>> first;
    std::shared_ptr<size_t> count;
    size_t index = 0;
};



#endif //LAB2_OOP_ITERATOR_H

