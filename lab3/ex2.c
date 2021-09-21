#include <stdio.h>
#include <stdlib.h>

#define SIZE 512

typedef struct pair {
    char key;
    int val;
} pair;

void output_row (const pair* arr, int count) {
    for (int i = 0; i < count; i++) {
        printf("%c ", arr[i].key);
        for (int j = 0; j < arr[i].val; j++) printf(".");
        printf("\n");
    }
}

int comp(const void* f, const void* s) {
    pair* first = (pair*) f;
    pair* second = (pair*) s;
    if (first->val < second->val) return 1;
    else if (first->val == second->val) {
        if ((int) first->key > (int) second->key) return 1;
        return -1;
    } else return -1;
}

int main() {
    pair arr[SIZE];
    char c;
    int index = 0, i = 0;
    do {
        scanf("%c", &c);
        if (c != ' ' && c != '\n' && c != '\0') {
            i = -1;
            while ((c != arr[++i].key) && (i < index));
            if (i >= index) {
                arr[i].key = c;
                index++;
            }
            arr[i].val++;
        }
    } while(c != '\n');
    qsort(arr, index, sizeof(pair), comp);
    output_row(arr, index);
    
    return 0;
}