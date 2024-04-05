#include "list.h"


List* init(fileLine line) {
    Node* root = (Node*) malloc(sizeof(Node));
    root->data = line;
    root->next = NULL;

    List* list = (List*) malloc(sizeof(List));
    list->first = root;
    return list;
}

void pushEnd(List* list, fileLine line) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = line;
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
