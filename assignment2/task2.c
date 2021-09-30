#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char Name[31];
typedef struct Date Date;
typedef struct Item Item;
typedef struct Resort Resort;

int check_name_char(char);
int check_date(Date*);
int leap_year(int);

int read_name(FILE*, char*);
int read_date(FILE*, Date*);
int read_item(FILE*, Item*);


int main() {
    FILE* fp = fopen("input.txt", "r");

    int flag = 1;
    Name name;
    Date date;
    // reading data
    flag *= read_name(fp, name);
    flag *= read_date(fp, &date);

    fclose(fp);

    return 0;
}

struct Date {
    int day;
    int month;
    int year;

    int hours;
    int minits;
    int seconds;
};

struct Item {
    char name[16];
    float size;
    int amount;
    char unit[6];
};

int leap_year(int y) {
    if (y % 4 == 0) {
        if (y % 100 == 0) {
            return y % 400 == 0;
        }
        return 1;
    }
    return 0;
}

int check_name_char(char c) {
    return (   ((int) c >= (int) 'a' && (int) c <= (int) 'z') 
            || ((int) c >= (int) 'A' && (int) c <= (int) 'Z') 
            || c == ' ');
}

int check_date(Date* date) {
    int max_day;

    if (date->year < 1) return 0;
    if (date->month < 1 || date->month > 12) return 0;

    if (date->month == 1 || date->month == 3
            || date->month == 5 || date->month == 7
            || date->month == 8 || date->month == 10
            || date->month == 12) {
        max_day = 31;
    } else if (date->month == 2) {
        if (leap_year(date->year)) max_day = 29;
        else max_day = 28;
    } else max_day = 30;

    if (date->day < 1 || date->day > max_day) return 0;

    if(date->hours > 23 || date->hours < 0) return 0;
    if(date->minits > 59 || date->minits < 0) return 0;
    if(date->seconds > 59 || date->seconds < 0) return 0;

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

int read_date(FILE* fp, Date* date) {
    fscanf(fp, "%d/%d/%d %d:%d:%d", &date->day, 
    &date->month, &date->year, &date->hours, &date->minits,
    &date->seconds);
    return check_date(date);
}