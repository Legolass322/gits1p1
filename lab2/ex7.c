#include <stdio.h>
#include <string.h>
#include "doublyLinkedList.c"


int main() {
    // Implementation with linked-list
    list rows = {"", 0, 0};
    printf("You can type some text. If you would like to finish then type '0'.\n");
    char* str = (char*) malloc(32*sizeof(char));
    scanf("%s", str);
    list_push_back(&rows, str);
    while (strcmp(str, "0") != 0) {
        str = (char*) malloc(32*sizeof(char));
        scanf("%s", str);
        list_push_back(&rows, str);
    }

    FILE* fp = fopen("output.txt", "w");
    for (int i = 1; i < list_len(&rows) - 1; i++) {
        fputs(strcat(list_val(&rows, i), " "), fp);
    }
    fclose(fp);
    list_free(&rows);
    return 0;
}