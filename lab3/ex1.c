#include <stdio.h>
#include <stdlib.h>

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

void output_col (const pair* carr, int count) {
    pair* arr = (pair*) malloc(sizeof(pair) * count);
    for (int i = 0; i < count; i++) arr[i] = carr[i];
    for (int i = 0; i < count; i++) {
        printf("%c ", arr[i].key);
    }
    printf("\n");
    int flag = 1;
    while (flag) {
        flag = 0;
        for (int i = 0; i < count; i++) {
            if (arr[i].val > 0) {
                printf(". ");
                flag += --arr[i].val;
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    free(arr);
    // for (int i = 0; i < count; i++) free(arr + i);
    // for (int i = count - 1; i >= 0; i--) free(arr + i);
}

int main() {
    pair arr[256];
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
    output_row(arr, index);
    output_col(arr, index);
    return 0;
}