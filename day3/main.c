#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)


int binary2decimal(char bin[], int length) {
    int decimal = 0;
    int w = 1;
    for(int i = length; i >= 0; --i) {
        if(bin[i] == '1') {
            decimal += w;
        }
        w *= 2;
    }
    return decimal;
}


void stripline(char *line) {
    int is_newline = strlen(line) - 1;
    if (line[is_newline] == '\n') {
        line[is_newline] = '\0';
    }
}


int main () {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *ptr;

    int idx = 0;
    int m = 0;
    int n;

    char *filename = "test.txt";

    TICK(TIME_A);

    fp = fopen(filename, "r");
    // Find how many lines the file has
    while ((read = getline(&line, &len, fp)) != -1)
        ++m;

    // And interpret the size of values from one line
    read = getline(&line, &len, fp);
    n = strlen(line) - 1;

    // Store the values to a separate container
    fp = fopen(filename, "r");
    char data[m][n];
    while ((read = getline(&line, &len, fp)) != -1) {
        for (int i = 0; i < n; ++i){
            data[idx][i] = line[i];
        }
        idx++;
    }

    printf("%d %d\n", n, m);

    int counts[n];
    for (int i = 0; i < n; ++i){
        counts[i] = 0;
    }

    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i){
            counts[i] += data[j][i] - '0';
        }
    }

    for (int i = 0; i < n; ++i){
        printf("%d,", counts[i]);
    }
    printf("\n%d\n", idx);

    char gamma_rate[n];
    char epsilon_rate[n];

    float numerator;
    float denominator = idx;
    for (int i = 0; i < n; ++i) {
        numerator = counts[i];
        int bit = round(numerator/denominator);
        if (bit == 1) {
            gamma_rate[i] = '1'; 
            epsilon_rate[i] = '0';
        } else {
            gamma_rate[i] = '0';
            epsilon_rate[i] = '1';
        }
    }
    int gamma = binary2decimal(gamma_rate, n - 1);
    int epsilon = binary2decimal(epsilon_rate, n - 1);

    printf("RES %d\n", gamma*epsilon);

    TOCK(TIME_A);

    return 1;
}
