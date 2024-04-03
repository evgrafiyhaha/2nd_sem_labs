#include "list.h"


List* init(fileLine line) {
    Node* root = (Node*) malloc(sizeof(Node));
    root->data = line;
    root->next = NULL;

    List* list = (List*) malloc(sizeof(List));
    list->first = root;
    return list;
}

void pushStart(List* list, fileLine line) {
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = line;
    node->next = list->first;

    list->first = node;
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

void deleteList(List* list) {
    Node* p = list->first;
    while (p->next) {
        Node* temp = p;
        p = p->next;
        free(temp);
    }
    //free(list->first);
    free(list);
}

void handleLines(List* list, void(*handler)(fileLine*)) {
    Node* p = list->first;

    if (p == NULL)
        return;

    do {
        handler(&(p->data));
        p = p->next;
    } while (p != NULL);
}

void printHandler(fileLine* line) {
    printf("%s ", line->region);//this is function for tests
}
