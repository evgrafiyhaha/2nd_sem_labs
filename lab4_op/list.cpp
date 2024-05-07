#include "list.h"


List* init(Point point) {
    Node* root = (Node*) malloc(sizeof(Node));
    root->data = point;
    root->next = NULL;

    List* list = (List*) malloc(sizeof(List));
    list->first = root;
    return list;
}

void pushEnd(List* list, Point point) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = point;
    node->next = NULL;
    if (list->first == NULL) {
        list->first = node;
    } else {
        Node* temp = list->first;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = node;
    }
}

void deleteList(List* list) {
    Node* p = list->first;
    while (p->next) {
        Node* temp = p;
        p = p->next;
        free(temp);
    }
    free(list);
}
