#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STUDENTS 150
#define INPUT "test2.txt"

struct S_table {
    char code[8];
    char name[64];
    float winter_s;
    float spring_s;
};
int readStudents(FILE *file, struct S_table students[], int *count) {
    char line[256];
    *count = 0;

    while (fgets(line, sizeof(line), file)) {
        char *pos;
        if ((pos = strchr(line, '\n')) != NULL) *pos = '\0';

        if (strcmp(line, "P") == 0) {
            break;
        }

        char code[8];
        float winter_s, spring_s;

        char *lastSpace = strrchr(line, ' ');
        if (!lastSpace) continue;
        if (sscanf(lastSpace + 1, "%f", &spring_s) != 1) continue;

        char *secondLastSpace = lastSpace - 1;
        while (secondLastSpace > line && *secondLastSpace != ' ') secondLastSpace--;
        if (*secondLastSpace != ' ') continue;
        if (sscanf(secondLastSpace + 1, "%f", &winter_s) != 1) continue;

        if (sscanf(line, "%7s", code) != 1) continue;

        char *nameStart = line + strlen(code);
        while (*nameStart == ' ') nameStart++;

        int nameLen = (int)(secondLastSpace - nameStart);
        if (nameLen > 63) nameLen = 63;  // с учётом увеличенного буфера

        char name[64];
        strncpy(name, nameStart, nameLen);
        name[nameLen] = '\0';

        strcpy(students[*count].code, code);
        strcpy(students[*count].name, name);
        students[*count].winter_s = winter_s;
        students[*count].spring_s = spring_s;

        (*count)++;
        if (*count >= 10) break;
    }

    return 0;
}
int readDeleteList(FILE *file, struct S_table students[], int *count) {
    char line[256];
    *count = 0;

    while (fgets(line, sizeof(line), file)) {
        char *pos;
        if ((pos = strchr(line, '\n')) != NULL) *pos = '\0';

        if (line[0] == '\0') continue;

        char code[8];
        if (sscanf(line, "%7s", code) != 1) continue;

        char *nameStart = line + strlen(code);
        while (*nameStart == ' ') nameStart++;

        char name[64];
        strncpy(name, nameStart, 63);
        name[63] = '\0';

        for (int i = strlen(name) - 1; i >= 0; i--) {
            if (name[i] == ' ') name[i] = '\0';
            else break;
        }

        strcpy(students[*count].code, code);
        strcpy(students[*count].name, name);
        students[*count].winter_s = 0.0f;
        students[*count].spring_s = 0.0f;

        (*count)++;
        if (*count >= 10) break;
    }

    return 0;
}

int binarySearch(struct S_table list[], int size, const char* code) {
    int left = 0, right = size - 1;

    while (left < right) {
        int mid = (left + right) / 2;
        if (strcmp(code, list[mid].code) <= 0)
            right = mid;
        else
            left = mid + 1;
    }

    if (strcmp(code, list[left].code) == 0)
        return left;
    else
        return -1;
}

void deleteStudents(struct S_table S[], int* sSize, struct S_table P[], int pSize) {
    for (int i = 0; i < pSize; ++i) {
        int index = binarySearch(S, *sSize, P[i].code);
        if (index != -1) {
            for (int j = index; j < *sSize - 1; ++j) {
                S[j] = S[j + 1];
            }
            (*sSize)--;
        }
    }
}

int main() {
    S_table S[MAX_STUDENTS];
    S_table P[MAX_STUDENTS];
    int s_size = 0, p_size = 0, flag = 1;
    char line[10];

    FILE *file = fopen(INPUT, "r");
    readStudents(file, S, &s_size);
    readDeleteList(file, P, &p_size);
    fclose(file);
    deleteStudents(S, &s_size, P, p_size);
    printf("Новый список:\n");
    for (int i = 0; i < s_size; i++) {
        printf("%s %s %.2f %.2f\n", S[i].code, S[i].name, S[i].winter_s, S[i].spring_s);
    }
    
}
