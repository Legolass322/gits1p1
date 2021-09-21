#include <stdio.h>

int strong(int n, const int* f) {
    int tmp = n;
    int sum = 0;
    while (tmp) {
        sum += f[tmp % 10];
        tmp = (int) tmp / 10;
    }
    if (sum == n) return 1;
    return 0;
}

int main() {
    int factorials[10];
    factorials[0] = 1;
    for (int i = 1; i < 10; i++) {
        factorials[i] = factorials[i - 1] * i;
    }

    int start, end;
    printf("Starting range of number: ");
    scanf("%d", &start);
    printf("Ending range of number: ");
    scanf("%d", &end);
    printf("\n");

    printf("The strong numbers are: ");
    for (int i = start; i < end; i++) {
        if (strong(i, factorials)) printf("%d; ", i);
    }
    return 0;
}