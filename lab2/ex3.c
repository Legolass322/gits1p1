#include <stdio.h>
#include <stdlib.h>

void stars() {
    int num;
    printf("Num of rows: ");
    scanf("%d", &num);
    int count = 1;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num - i; j++) {
            printf(" ");
        }
        for (int j = 0; j < count; j++) {
            printf("*");
        }
        count += 2;
        printf("\n");
    }
}

void rectangle() {
    int row, col;
    printf("Num of rows: ");
    scanf("%d", &row);
    printf("Num of cols: ");
    scanf("%d", &col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++, printf("*"));
        printf("\n");
    }
}

void arrow() {
    int n;
    printf("Num of rows: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        if (i < n / 2 + n % 2) {
            for (int j = 0; j < i + 1; j++) printf("*");
        } else {
            for (int j = 0; j < n - i; j++) printf("*");
        }
        printf("\n");
    }
}

int main() {
    char c;
    printf("Type 's', 'r', or 'a' to draw diffrent pictures with '*': ");
    scanf("%c", &c);
    if (c == 'a') {
        arrow();
    } else if( c == 's') {
        stars();
    } else if ( c == 'r') {
        rectangle();
    }
}