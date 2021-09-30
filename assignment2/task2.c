#include <stdio.h>
#include <string.h>

typedef char Name[31];
typedef struct Date Date;
typedef struct Item Item;
typedef struct Resort Resort;

struct Date {
    int day;
    int month;
    int year;

    int hours;
    int minits;
    int seconds;
};

int check_name_char(char);
int check_date(Date);
int ckeck_item(Item);

int read_name(FILE*, char*);


int check_name_char(char c) {
    if (!(((int) c >= (int) 'a' && (int) c <= (int) 'z') || ((int) c >= (int) 'A' && (int) c <= (int) 'Z') || c == ' '))
        return 0;
    return 1;
}

int read_name(FILE* fp, char* name) {
    char c = 0;
    int length;
    while (c != '\n' && length <= 30) {
        c = fgetc(fp);
        if (!check_name_char(c)) return 0;
        *(name + length) = c;
        length += 1;
        if (length > 30) {
            return 0;
        }
    }
    return 1;
}

int main() {
    FILE* fp = fopen("input.txt", "r");

    int flag = 1;
    // reading name
    Name name;
    flag *= read_name(fp, name);
    
    return 0;
}