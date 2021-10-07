#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char Name[31];
typedef struct Date Date;
typedef struct Item Item;
typedef struct Row Row;

int is_leap_year(int);
int is_digit(char);
int is_alpha(char);

int check_name_char(char);
int check_date(Date*);
int check_size(char*);

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

struct Item {
    char name[16];
    char size[16];
    int amount;
    char unit[6];
};

struct Row {
    int count_item;
    Name name;
    Date date;
    Item items[10];
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

int check_size(char* buf) {
    /* float (0; 200] */
    for (int i = 0; i < strlen(buf); i++) {
        if (!is_digit(*(buf + i)) && *(buf + i) != '.') return 0; // fix: 16.16.16
    }
    char* end;
    float f = strtof(buf, &end);
    if (f <= 0 ||  f > 200) return 0;

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
            if (!(is_digit(*(buffer + i)) || *(buffer + i) == ' ')) return 0;
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

int read_item(char* buffer, Item* item) {
    int length = strlen(buffer);
    char tmp_buf[32];
    char *pend;
    // backward reading
    int i = length;
    int end = length;

    while (*(buffer + i) == ' ' && i >= 0) i--, end--; // useless spaces
    while (*(buffer + i) != ' ' && i >= 0) i--; // units
    for (int j = i + 1; j < end + 1; j++) {
        tmp_buf[j - i - 1] = *(buffer + j);
    }
    tmp_buf[end - i] = '\0';
    end = i;
    if (!(strcmp(tmp_buf, "pcs\0") == 0 || strcmp(tmp_buf, "pair\0") == 0)) return 0;
    strcpy(item->unit, tmp_buf);

    while (*(buffer + i) == ' ' && i >= 0) i--, end--; // useless spaces
    while (*(buffer + i) != ' ' && i >= 0) i--; // amount
    for (int j = i + 1; j < end + 1; j++) {
        tmp_buf[j - i - 1] = *(buffer + j);
    }
    tmp_buf[end - i] = '\0';
    end = i;
    item->amount = strtol(tmp_buf, &pend, 10);
    if (item->amount > 1 && strcmp(item->unit, "pair\0") == 0) {
        item->unit[4] = 's';
        item->unit[5] = '\0';
    }

    while (*(buffer + i) == ' ' && i >= 0) i--, end--; // useless spaces
    while (*(buffer + i) != ' ' && i >= 0) i--; // size
    for (int j = i + 1; j < end + 1; j++) {
        item->size[j - i - 1] = *(buffer + j);
    }
    item->size[end - i] = '\0';
    end = i;
    if (!check_size(item->size)) return 0;

    while (*(buffer + i) == ' ' && i >= 0) i--, end--; // useless spaces
    i = 0; // name
    if (end + 1 < 4 || end + 1 > 15) return 0;
    for (int j = i; j < end + 1; j++) {
        if (!check_name_char(*(buffer + j))) return 0;
        (*item).name[j - i] = *(buffer + j);
    }
    return 1;
}

int main() {
    char buffer[100];
    int flag = 1;

    int count = 0;
    Row resort[30];

    FILE* fp = fopen("input.txt", "r");
    FILE* op = fopen("output.txt", "w");

    // reading
    char c = 0;
    while (c != EOF) {
        // name
        fscanf(fp, "%[^\n]\n", buffer);
        flag *= read_name(buffer, resort[count].name);
        if (!flag) {
            fprintf(op, "Invalid input!");
            return 0;
        }
        // date&time
        fscanf(fp, "%[^\n]\n", buffer);
        flag *= read_date(buffer, &(resort[count].date));
        if (!flag) {
            fprintf(op, "Invalid input!");
            return 0;
        }
        // items
        int is_next = 0;
        int i = 0;
        resort[count].count_item = 0;
        do {
            i = 0;
            c = fgetc(fp);
            while (c != '\n' && c != EOF) {
                buffer[i] = c;
                i++;
                c = fgetc(fp);
            }
            buffer[i] = '\0';
            if (strlen(buffer) == 0) {
                if (resort[count].count_item == 0) {
                    fprintf(op, "Invalid input!");
                    return 0;
                }
                is_next = 1;
            } else {
                flag *= read_item(buffer, &(resort[count].items[resort[count].count_item]));
                if (!flag) {
                    fprintf(op, "Invalid input!");
                    return 0;
                }
                resort[count].count_item++;
            }
        } while (c != EOF && !is_next);
        count++;
    }

    // writting
    for (int i = 0; i < count; i++) {
        fprintf(op, "%s ", resort[i].name);
        fprintf(op, "has rented ");
        for (int j = 0; j < resort[i].count_item; j++) {
            fprintf(op, "%d ", resort[i].items[j].amount);
            fprintf(op, "%s ", resort[i].items[j].unit);
            fprintf(op, "of ");
            fprintf(op, "%s ", resort[i].items[j].name);
            fprintf(op, "of size ");
            fprintf(op, "%s", resort[i].items[j].size);
            if (j != resort[i].count_item - 1) {
                if (resort[i].count_item - j - 2 == 0)
                    fprintf(op, " and ");
                else fprintf(op, ", ");
            }
        }
        fprintf(op, " on ");
        fprintf(op, "%s ", resort[i].date.str_date);
        fprintf(op, "at ");
        fprintf(op, "%s.", resort[i].date.str_time);
        if (i != count - 1) fprintf(op, "\n");
    }
    fprintf(op, "\n");
    fclose(fp);
    fclose(op);
    return 0;
}