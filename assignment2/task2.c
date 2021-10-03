#include <stdio.h>
#include <string.h>

typedef char Name[31];
typedef struct Date Date;
typedef struct Item Item;
typedef struct Resort Resort;

int is_leap_year(int);
int is_digit(char);
int is_alpha(char);

int check_name_char(char);
int check_date(Date*);

int read_name(char*, char*);
int read_date(char*, Date*);
int read_item(char*, Item*);


struct Date {
    int day;
    int month;
    int year;

    int hours;
    int minits;
    int seconds;

    char str_date[11];
    char str_time[9];
};


int is_leap_year(int y) {
    if (y % 4 == 0) {
        if (y % 100 == 0) {
            return y % 400 == 0;
        }
        return 1;
    }
    return 0;
}

int is_digit(char c) {
    return (int) c >= (int) '0' && (int) c <= '9';
}

int is_alpha(char c) {
    return (   ((int) c >= (int) 'a' && (int) c <= (int) 'z') 
            || ((int) c >= (int) 'A' && (int) c <= (int) 'Z'));
}

int check_name_char(char c) {
    return (is_alpha(c) || c == ' ');
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
        if (is_leap_year(date->year)) max_day = 29;
        else max_day = 28;
    } else max_day = 30;

    if (date->day < 1 || date->day > max_day) return 0;

    if(date->hours > 23 || date->hours < 0) return 0;
    if(date->minits > 59 || date->minits < 0) return 0;
    if(date->seconds > 59 || date->seconds < 0) return 0;

    return 1;
}

int read_name(char* buffer, char* name) {
    /* name : [2;30] */
    int len = strlen(buffer);
    if (len < 2 || len > 30) return 0;

    char *tmpb = buffer;
    char *tmpn = name;
    do {
        if (!(check_name_char(*(tmpb)) || *(tmpb) == '\0')) return 0;
        else *(tmpn++) = *(tmpb++);
    } while(*tmpb != '\0');

    return 1;
}

int read_date(char* buffer, Date* date) {
    // checking format
    if (strlen(buffer) != 19) return 0;

    for(int i = 0; i < 19; i++) {
        if (i == 2 || i == 5)
            if (*(buffer + i) != '/') return 0;
        else if (i == 13 || i == 16)
            if (*(buffer + i) != ':') return 0;
        else 
            if (!is_digit(*(buffer + i)) || *(buffer + i) != ' ') return 0;
    }

    // reading str values
    for (int i = 0; i < 10; i++) {
        date->str_date[i] = *(buffer + i);
    }
    date->str_date[10] = '\0';
    for (int i = 11; i < 19; i++) {
        date->str_time[i - 11] = *(buffer + i);
    }
    date->str_time[8] = '\0';

    // reading int values
    sscanf(buffer, "%d/%d/%d %d:%d:%d", &((*date).day), &((*date).month),
        &((*date).year), &((*date).hours), &((*date).minits), &((*date).seconds));

    // checking values
    return check_date(date);
}

int main() {
    char buffer[100];
    int flag = 1;

    Name name;
    Date date;

    FILE* fp = fopen("input.txt", "r");

    fscanf(fp, "%[^\n]\n", buffer);
    flag *= read_name(buffer, name);
    if (!flag) printf("Invalid1");
    fscanf(fp, "%[^\n]\n", buffer);
    flag *= read_date(buffer, &date);
    if (!flag) printf("Invalid1");;

    fclose(fp);

    printf("%s %s %d", date.str_date, date.str_time, flag);

    return 0;
}