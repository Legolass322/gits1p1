#include <stdio.h>
#include <string.h>

int main() {
    char word[300];
    char data[300][300];
    int width;

    // reading word by word
    char c;
    int count = 0; // number of words
    int length = 0; // length of current word 
    FILE* fp = fopen("input.txt", "r");
    do {
        c = fgetc(fp);
        if (c == ' ' || c == '\n') { // move word to array of words
            word[length] = '\0';
            strcpy(data[count], word);
            data[count];
            length = 0;
            count += 1;
        } else { // move char to buffer
            word[length] = c;
            length += 1;
        }
    } while (c != '\n');
    fscanf(fp, "%d", &width);
    fclose(fp);

    // printing
    int index = 0; // number of printed words
    int i = 0; // index + number of buffered words
    int cur_space;
    int remainder;
    int min_space;
    fp = fopen("output.txt", "w");
    while (index < count) {
        // calculating
        cur_space = width;
        remainder = 0;
        min_space = 0;
        i = 0;
        cur_space -= strlen(data[index]);
        i++;
        while (cur_space >= strlen(data[index + i]) + 1 && index + i < count) {
            cur_space -= strlen(data[index + i]) + 1;
            i++;
        }
        if (i != 1) {
            min_space = cur_space / (i - 1) + 1;
            remainder = cur_space % (i - 1);
        } else {
            min_space = 0;
            remainder = 0;
        }

        // printing
        fprintf(fp, "%s", data[index]);
        for (int j = index + 1; j < i + index; j++) {
            for (int space = 0; space < min_space + (int) (remainder > 0); space++) {
                fprintf(fp, " ");
            }
            remainder > 0 ? remainder--: 0;
            fprintf(fp, "%s", data[j]);
        }
        index += i;
        if (index != count) fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}