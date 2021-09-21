#include <stdio.h>

int main() {
    int x, y;
    scanf("%d", &x);
    scanf("%d", &y);
    printf("\nx = %d, y = %d\n", x, y);
    printf("x + y = %d \n", x + y);
    printf("x - y = %d \n", x - y);
    printf("x * y = %d \n", x * y);
    if (y == 0) {
        printf("y should be a nonzero value");
    } else {
        printf("x / y = %f", (float) x / y);
    }
    return 0;
}
