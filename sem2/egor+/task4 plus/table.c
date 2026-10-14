#include <stdio.h>
#include <string.h>

// #define 150 150
#define INPUT "test1.txt"

struct table {
    char code[8];
    char name[64];    // увеличен буфер имени
    float winter_s;
    float spring_s;
};

int readS(FILE *file, struct table students[], int *count) {
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
        if (*count >= 150) break;
    }
    return 0;
}
int readP(FILE *file, struct table students[], int *count) {
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

        // Обрезаем пробелы справа
        for (int i = strlen(name) - 1; i >= 0; i--) {
            if (name[i] == ' ') name[i] = '\0';
            else break;
        }

        strcpy(students[*count].code, code);
        strcpy(students[*count].name, name);
        students[*count].winter_s = 0.0f;
        students[*count].spring_s = 0.0f;

        (*count)++;
        if (*count >= 150) break;
    }

    return 0;
}

int find3(struct table list[], int size, const char* code) {
    int l = 0, r = size - 1;
    while (l < r) {
        int c = (l + r) / 2;
        if (strcmp(code, list[c].code) <= 0)
            r = c;
        else
            l = c + 1;
    }
    if (strcmp(code, list[l].code) == 0)
        return l;
    else
        return -1;
}

void deletetable(struct table S[], int* sSize, struct table P[], int pSize) {
    for (int i = 0; i < pSize; ++i) {
        int index = find3(S, *sSize, P[i].code);
        if (index != -1) {
            for (int j = index; j < *sSize - 1; ++j) {
                S[j] = S[j + 1];
            }
            (*sSize)--;
        }
    }
}


void printList(struct table S[], int size) {
    printf("Новый список студентов:\n");
    for (int i = 0; i < size; i++) {
        printf("%s %s %.2f %.2f\n", S[i].code, S[i].name, S[i].winter_s, S[i].spring_s);
    }
}

int main() {
    struct table S[150], P[150];
    int sSize = 0, pSize = 0;

    FILE *file = fopen(INPUT, "r");
    if (!file) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }

    char section[10];
    if (fscanf(file, "%9s", section) != 1) {
        printf("Ошибка чтения файла.\n");
        fclose(file);
        return 1;
    }

    if (strcmp(section, "S") != 0) {
        printf("Ожидался раздел S.\n");
        fclose(file);
        return 1;
    }

    readS(file, S, &sSize);
    readP(file, P, &pSize);

    fclose(file);

    deletetable(S, &sSize, P, pSize);
    printList(S, sSize);

    return 0;
}
