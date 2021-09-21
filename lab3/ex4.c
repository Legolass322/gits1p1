#include <stdio.h>

int main() {
    int num;
    scanf("%d", &num);
    int i = 0;
    int row = 1;
    while (row <= num) {
        for (int j = 0; j < num - row; j++) printf(" ");
        for (int j = 0; j < row; j++) {
            printf("%d", i);
            i++;
        }
        printf("\n");
        row++;
    }
    return 0;
}