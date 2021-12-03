#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)


struct Coordinate {
    int x;
    int y;
    int aim;
};

const char *FORWARD = "forward";
const char *DOWN = "down";
const char *UP = "up";


void move_naive(struct Coordinate *p, char *ins, int v) {
    if (strcmp(ins, FORWARD) == 0) {
        p->x = p->x + v;
    } else if (strcmp(ins, DOWN) == 0) {
        p->y = p->y + v;
    } else if (strcmp(ins, UP) == 0) {
        p->y = p->y - v;
    } else {
        printf("Something might have been missed");
    }
}


void move_real(struct Coordinate *p, char *ins, int v) {
    if (strcmp(ins, FORWARD) == 0) {
        p->x = p->x + v;
        p->y = p->y + (v * p->aim);
    } else if (strcmp(ins, DOWN) == 0) {
        p->aim = p->aim + v;
    } else if (strcmp(ins, UP) == 0) {
        p->aim = p->aim - v;
    } else {
        printf("Something might have been missed");
    }
}

int main() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *ptr;

    char *token;
    int i = 0;

    struct Coordinate naive = {0, 0, 0};
    struct Coordinate real = {0, 0, 0};

    TICK(TIME_A);
    fp = fopen("input.txt", "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        int is_newline = strlen(line) - 1;
        if (line[is_newline] == '\n') {
            line[is_newline] = '\0';
        }

        char *v[2];
        i = 0;
        for (token = strtok(line, " "); token; token = strtok(NULL, " ")) {
            v[i] = token;
            i = i + 1;
        }

        char *instruction = v[0];
        int value = strtol(v[1], &ptr, 10);

        move_naive(&naive, instruction, value);
        move_real(&real, instruction, value);
    }
    TOCK(TIME_A);

    printf("Task 1: %d\n", naive.x*naive.y);
    printf("Task 2: %d\n", real.x*real.y);
    return 1;
}
