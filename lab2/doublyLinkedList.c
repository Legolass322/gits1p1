#include <stdlib.h>


typedef char* list_t;
typedef struct list_node list_node, *pno, list;

pno list_create_node(list_t);
void list_push_back(pno, list_t);
void list_push_front(pno, list_t);
void list_insert(pno, int, list_t);
void list_remove(pno, int);
void list_remove_back(pno);
void list_remove_front(pno);
void list_free(pno);
list_t list_val(pno, int);
int list_len(pno);


struct list_node {
    list_t value;
    pno next_node;
    pno previous_node;
};


pno list_create_node(list_t val) {
    pno L = (list_node*) malloc(sizeof(list_node));
    L->value = val;
    L->next_node = 0;
    L->previous_node = 0;
    return L;
}

void list_push_back(pno L, list_t val) {
    pno tmp = L;
    while(tmp->next_node) tmp = tmp->next_node;

    pno new_node = list_create_node(val);
    tmp->next_node = new_node;
    new_node->previous_node = tmp;
}

void list_push_front(pno L, list_t val) {
    pno tmp = L;
    while(tmp->previous_node) tmp = tmp->previous_node;

    pno new_node = list_create_node(val);
    tmp->previous_node = new_node;
    new_node->next_node = tmp;
    L = new_node;
}

void list_insert(pno L, int index, list_t val) {
    pno tmp = L;
    while(tmp->previous_node) tmp = tmp->previous_node;

    int i = 0;
    while (i != index && tmp->next_node) {
        i++;
        tmp = tmp->next_node;
    }
    if (i != index) {
        // unexpected behavior
    }

    pno new_node = list_create_node(val);
    new_node->next_node = tmp;
    new_node->previous_node = tmp->previous_node;
    if (tmp->previous_node) {
        tmp->previous_node->next_node = new_node;
    }
    tmp->previous_node = new_node;

    while(tmp->previous_node) tmp = tmp->previous_node;
    L = tmp;
}

void list_remove(pno L, int index) {
    pno tmp = L;
    while(tmp->previous_node) tmp = tmp->previous_node;

    int i = 0;
    while (i != index && tmp->next_node) {
        i++;
        tmp = tmp->next_node;
    }
    if (i != index) {
        // unexpected behavior
    }

    pno prev = tmp->previous_node;
    pno next = tmp->next_node;
    free(tmp);
    tmp = prev;
    if (prev) prev->next_node = next;
    if (next) { 
        next->previous_node = prev;
        tmp = next;
    }

    while(tmp->previous_node) tmp = tmp->previous_node;
    if (tmp) L = tmp;
}

void list_remove_back(pno L) {
    pno tmp = L;
    while(tmp->next_node) tmp = tmp->next_node;

    if (!tmp) {
        // unexpected behavior
    }

    pno prev = tmp->previous_node;
    free(tmp);
    tmp = prev;
    if (prev) prev->next_node = 0;

    while(tmp->previous_node) tmp = tmp->previous_node;
    if (tmp) L = tmp;
}

void list_remove_front(pno L) {
    pno tmp = L;
    while(tmp->previous_node) tmp = tmp->previous_node;

    if (!tmp) {
        // unexpected behavior
    }

    pno next = tmp->next_node;
    free(tmp);
    tmp = next;
    if (next) next->previous_node = 0;
    if (tmp) L = tmp;
}

void list_free(pno L) {
    pno left = L->previous_node;
    pno right = L->next_node;
    while(left) {
        pno tmp = left->previous_node;
        free(left);
        left = tmp;
    }
    while(right) {
        pno tmp = right->next_node;
        free(right);
        right = tmp;
    }
    free(L);
    L = 0;
}

list_t list_val(pno L, int index) {
    pno tmp = L;
    while(tmp->previous_node) tmp = tmp->previous_node;

    int i = 0;
    while (i != index && tmp->next_node) {
        i++;
        tmp = tmp->next_node;
    }

    if (index == i) {
        return tmp->value;
    }
    // else - unexpected behavior - throw exception
}

int list_len(pno L) {
    pno tmp = L;
    while(tmp->previous_node) tmp = tmp->previous_node;

    int count = 0;
    while (tmp) {
        count++;
        tmp = tmp->next_node;
    }
    return count;
}