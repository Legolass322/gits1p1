#include <stdio.h>
#include "doublyLinkedList.c"

int main() {
    char str[255];
    list linkedList = {"first", 0, 0};
    list_push_back(&linkedList, "second");
    list_push_back(&linkedList, "third");
    list_push_back(&linkedList, "fourth");
    list_push_front(&linkedList, "fifth");
    list_insert(&linkedList, 2, "sixth");
    scanf("%[^\n]%*\n", str);
    list_push_back(&linkedList, str);

    printf("\n");
    for (int i = 0; i < list_len(&linkedList); i++) {
        printf("%s\n", list_val(&linkedList, i));
    }
    printf("%d", list_len(&linkedList));
    list_free(&linkedList);
    return 0;
}