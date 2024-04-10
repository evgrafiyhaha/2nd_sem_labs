#include "list.h"


List* init(FileLine line) {
    Node* root = (Node*) malloc(sizeof(Node));
    root->data = line;
    root->next = NULL;

    List* list = (List*) malloc(sizeof(List));
    list->first = root;
    return list;
}

void pushEnd(List* list, FileLine line) {
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

void deleteList(List* list) {
    Node* p = list->first;
    while (p->next) {
        Node* temp = p;
        p = p->next;
        free(temp);
    }
    free(list);
}
