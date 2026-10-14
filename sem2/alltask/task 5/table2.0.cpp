#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT "test7.txt"        
#define TABLE_SIZE 10

struct tableElement{
    char name[32];
    char type[16];
    int size;
    int componentCount;
    char componentType[16];
    int isOccupied;
    int hash;
    int usageCount;
};

int hash(char *name, int tableSize){
    unsigned long long value = 0;
    for (int i = 0; name[i] != '\0'; i++){
        value = value*31 + name[i];
    }
    return value % tableSize;
}

int insert(struct tableElement *table, int tableSize, struct tableElement element) {
    int index = hash(element.name, tableSize);
    int success = 0;

    for (int i = 0; i < tableSize && !success; i++) {
        int probeIndex = (index + i) % tableSize;

        if (!table[probeIndex].isOccupied) {
            table[probeIndex] = element;
            table[probeIndex].isOccupied = 1;
            table[probeIndex].hash = index;
            success = 1;
        }
    }
    return success;
}

void printTable(struct tableElement *table, int tableSize) {
    printf("Таблица имен:\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("hash  | №   | %-30s | %-12s | %-6s | %-6s | %-16s | %-6s |\n", "Имя", "Тип", "Размер", "Кол-во", "Тип компонент", "Исп.");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < tableSize; i++) {
        if (table[i].isOccupied) {
            printf("%-5d| %-3d | %-30s | %-12s | %-6d | %-6d | %-16s | %-6d |\n",
                table[i].hash,
                i,
                table[i].name,
                table[i].type,
                table[i].size,
                table[i].componentCount,
                table[i].componentType,
                table[i].usageCount);
        }
    }

    printf("----------------------------------------------------------------------------------\n");
}

int getSizeOfType(const char *type) {
    int size = 0;
    if (strcmp(type, "char") == 0) size = 1;
    else if (strcmp(type, "short") == 0) size = 2;
    else if (strcmp(type, "int") == 0) size = 4;
    else if (strcmp(type, "long") == 0) size = 8;
    else if (strcmp(type, "unsigned int") == 0) size = 4;
    else if (strcmp(type, "unsigned long") == 0) size = 8;
    else if (strcmp(type, "float") == 0) size = 4;
    else if (strcmp(type, "double") == 0) size = 8;
    else if (strcmp(type, "long double") == 0) size = 16;

    return size; 
}

int is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

void incrementUsage(struct tableElement *table, int tableSize, const char *name) {
    for (int i = 0; i < tableSize; i++) {
        if (table[i].isOccupied && strcmp(table[i].name, name) == 0) {
            table[i].usageCount++;
            break;
        }
    }
}

int parseLine(const char *line, struct tableElement *elem, struct tableElement *table, int tableSize) {
    memset(elem, 0, sizeof(struct tableElement));

    char buffer[257];
    strncpy(buffer, line, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char *start = buffer;
    while (is_space((unsigned char)*start)) start++;
    char *end = start + strlen(start) - 1;
    while (end > start && is_space((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
    int len = strlen(start);
    if (len > 0 && start[len - 1] == ';') {
        start[len - 1] = '\0';
    }
    
    char *p = start;

    // Проверяем, начинается ли строка с if
    int isIfStatement = 0;
    if (strncmp(p, "if", 2) == 0 && (is_space(p[2]) || p[2] == '(')) {
        isIfStatement = 1;
        p += 2;
        while (*p && is_space((unsigned char)*p)) p++;
        if (*p == '(') p++;
        while (*p && is_space((unsigned char)*p)) p++;
    }

    char typePart1[16] = {0};
    int i = 0;
    while (*p && !is_space((unsigned char)*p) && *p != '*' && *p != '=' && *p != '[' && *p != '&' && *p != '(' && *p != ')' && i < 15) {
        typePart1[i++] = *p++;
    }
    typePart1[i] = '\0';

    // Если первое слово не является известным типом, обрабатываем как оператор
    if (strcmp(typePart1, "char") != 0 && strcmp(typePart1, "short") != 0 &&
        strcmp(typePart1, "int") != 0 && strcmp(typePart1, "long") != 0 && 
        strcmp(typePart1, "unsigned") != 0 && strcmp(typePart1, "float") != 0 && 
        strcmp(typePart1, "double") != 0) {
        
        // Это оператор, обрабатываем использование переменных
        char *token = strtok(buffer, " \t\n[]*=&;()");
        while (token != NULL) {
            if (strcmp(token, "if") != 0 && strcmp(token, "else") != 0) {
                incrementUsage(table, tableSize, token);
            }
            token = strtok(NULL, " \t\n[]*=&;()");
        }
        return 0; // Не добавляем новую запись в таблицу
    }

    // Оригинальная обработка объявлений переменных
    while (*p && is_space((unsigned char)*p)) p++;

    char typePart2[16] = {0};
    if (*p && !(*p == '*' || *p == '\0' || *p == '[' || *p == '=' || *p == '&')) {
        i = 0;
        char *tmp = p;
        while (*tmp && !is_space((unsigned char)*tmp) && *tmp != '*' && *tmp != '[' && *tmp != '=' && *tmp != '&' && i < 15) {
            typePart2[i++] = *tmp++;
        }
        typePart2[i] = '\0';

        if ((strcmp(typePart1, "unsigned") == 0 && (strcmp(typePart2, "int") == 0 || strcmp(typePart2, "long") == 0)) 
            || (strcmp(typePart1, "long") == 0 && strcmp(typePart2, "double") == 0)) {
            p = tmp;
        } else {
            typePart2[0] = '\0';
        }
    }

    char baseType[32] = {0};
    strcpy(baseType, typePart1);
    if (typePart2[0]) {
        strcat(baseType, " ");
        strcat(baseType, typePart2);
    }

    while (*p && is_space((unsigned char)*p)) p++;

    int pointerCount = 0;
    while (*p == '*') {
        pointerCount++;
        p++;
        while (*p && is_space((unsigned char)*p)) p++;
    }

    char varName[32] = {0};
    i = 0;
    while (*p && *p != '[' && *p != '=' && *p != '&' && !is_space((unsigned char)*p) && i < 31) {
        varName[i++] = *p++;
    }
    varName[i] = '\0';

    if (strlen(varName) == 0) return 0;
    strcpy(elem->name, varName);
    incrementUsage(table, tableSize, varName);

    while (*p && is_space((unsigned char)*p)) p++;

    int isArray = 0;
    int componentCount = 0;

    if (*p == '[') {
        isArray = 1;
        p++;
        if (*p == ']') {
            componentCount = 0;
            p++;
        } else {
            int value = 0;
            while (*p && *p != ']') {
                if (*p >= '0' && *p <= '9') {
                    value = value * 10 + (*p - '0');
                }
                p++;
            }
            componentCount = value;
            if (*p == ']') p++; else return 0;
        }
        while (*p && is_space((unsigned char)*p)) p++;
    }

    // Пропускаем инициализацию (все что после =)
    if (*p == '=') {
        p++;
        while (*p && is_space((unsigned char)*p)) p++;
        
        // Если это указатель и идет &, увеличиваем использование переменной
        if (*p == '&') {
            p++;
            char refVar[32] = {0};
            i = 0;
            while (*p && !is_space((unsigned char)*p) && *p != ';' && i < 31) {
                refVar[i++] = *p++;
            }
            refVar[i] = '\0';
            incrementUsage(table, tableSize, refVar);
        }
        // Пропускаем остальное до ;
        while (*p && *p != ';') p++;
    }

    if (pointerCount > 0) {
        strcpy(elem->type, "pointer");
        if (pointerCount > 1) {
            strcpy(elem->componentType, "pointer");
        } else {
            strncpy(elem->componentType, baseType, sizeof(elem->componentType) - 1);
        }
        elem->componentCount = 0;
        elem->size = 8;
    } else if (isArray) {
        strcpy(elem->type, "array");
        strncpy(elem->componentType, baseType, sizeof(elem->componentType) - 1);
        elem->componentCount = componentCount;
        int baseSize = getSizeOfType(baseType);
        elem->size = (componentCount == 0) ? 0 : baseSize * componentCount;
    } else {
        strncpy(elem->type, baseType, sizeof(elem->type) - 1);
        elem->componentType[0] = '\0';
        elem->componentCount = 0;
        elem->size = getSizeOfType(baseType);
    }

    elem->isOccupied = 0;
    elem->usageCount = 0;
    return 1;
}

int main() {
    struct tableElement table[TABLE_SIZE] = {0};
    char line[257];
    int result = 0;

    FILE *file = fopen(INPUT, "r");
    if (!file) {
        printf("Не удалось открыть файл \n");
        result = 1;
    } else {
        while (fgets(line, sizeof(line), file) && result == 0) {
            line[strcspn(line, "\r\n")] = 0;

            struct tableElement elem = {0};
            if (parseLine(line, &elem, table, TABLE_SIZE)) {
                if (!insert(table, TABLE_SIZE, elem)) {
                    printf("Не удалось добавить элемент %s - таблица заполнена\n", elem.name);
                }
            }
        }
        fclose(file);
    }

    printTable(table, TABLE_SIZE);

    return result;
}