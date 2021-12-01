#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int window_sum(int w[], int ws) {
    int count = 0;
    int value = 0;
    for (int j = 0; j < ws; j++ ) {
        value = w[j];
        count = count + value;
        if (!value) {
            return 0;
        }
    }
    return count;
}


int num_from_line(char *line) {
    char *ptr;
    int is_newline = strlen(line) - 1;
    if (line[is_newline] == '\n') {
        line[is_newline] = '\0';
    }
    return strtol(line, &ptr, 10);
}


int main() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int idx = 0;

    int value;
    int prev = 0;
    int n = 0;

    // Sliding window
    int sw = 0;

    int window_size = 3;
    int window[window_size];

    int wvalue;
    int wprev = 0;
    int wn = 0;

    clock_t begin = clock();
    fp = fopen("input.txt", "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        value = num_from_line(line);

        // Task 1.
        if (prev && prev < value) {
            n = n + 1;
        }

        // Task 2.
        sw = idx % window_size;
        window[sw] = value;
        int wvalue = window_sum(window, window_size);
        if (wvalue && wprev && wprev < wvalue) {
            wn = wn + 1;
        }

        prev = value;
        wprev = wvalue;
        idx = idx + 1;
    }

    printf("%d %d\n", n, wn);
    fclose(fp);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
    return 0;
}
