#include <stdio.h>
#include "list.c"

int main() {
    int n;
    scanf("%d", &n);
    pno list = list_create_node(n);
    while (n >= 0) {
        scanf("%d", &n);
        if (n >= 0 && !list_find(list, n))
            list_push_back(list, n);
    }
    for (int i = 0; i < list_len(list); i++) {
        printf("%d ", list_val(list, i));
    }
}