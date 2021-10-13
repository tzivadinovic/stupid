#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define INP_LEN 32

void first_word(char *);

struct info {
    char name[64];
    char course[64];
    char type[64];
};

void populate_data(struct info *data) {
    char *name = getenv("STUPID_NAME");
    char *course = getenv("STUPID_COURSE");
    if (name == NULL || course == NULL) {
        errno = ENODATA;
        perror("STUPID_NAME, STUPID_COURSE");
        exit(EXIT_FAILURE);
    }
    char s[INP_LEN];
    printf("Assignment type: ");
    fgets(s, INP_LEN, stdin);
    first_word(s);
    strcpy(data->name, name);
    strcpy(data->course, course);
    strcpy(data->type, s);
}

int main() {
    char folder_name[256];
    struct info *data = calloc(1, sizeof(struct info));
    populate_data(data);
    snprintf(folder_name, 256, "%s_%s_%s", data->course, data->type, data->name);
    char command[256] = {0};
    strcat(command, "mkdir -p ");
    strcat(command, folder_name);
    system(command);
    free(data);
    return 0;
}

void first_word(char *str) {
    while (*str != '\0') {
        if (isspace(*str)) {
            *str = 0;
        }
        str++;
    }
}
