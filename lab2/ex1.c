#include <stdio.h>
#include <string.h>

void reverse(char* str) {
    char c;
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        c = str[length - i - 1];
        str[length - i - 1] = str[i];
        str[i] = c;
    }
}

int main() {
    char str[100];
    scanf("%[^\n]", str);
    printf("%s\n", str);
    reverse(str);
    printf("%s", str);
    return 0;
}