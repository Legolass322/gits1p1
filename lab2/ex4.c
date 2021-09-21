#include <stdio.h>
#include "swap.c"

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    swap(&a, &b);
    printf("first = %d, second = %d", a, b);
    return 0;
}