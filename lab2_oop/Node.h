#ifndef LAB2_OOP_NODE_H
#define LAB2_OOP_NODE_H

template <typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next;
};

#endif //LAB2_OOP_NODE_H
