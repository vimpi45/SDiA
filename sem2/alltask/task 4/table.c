    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define INPUT "test7.txt"        
    #define TABLE_SIZE 8
    // допуск сдан стр 109 назначение циклов и добавить подсчет числа просмотров
 // 5 пз ==== 3г стр 119 метод шелла 1.1а
    struct tableElement{
    char name[32];
    char type[16];
    int size;
    int componentCount;
    char componentType[16];
    int isOccupied;
    int hash;
    };

    int hash(char *name, int tableSize){
        unsigned long long value = 0;
        for (int i = 0; name[i] != '\0'; i++){
        value = value*31  + name[i];
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
        printf("hash  | №   | %-30s | %-12s | %-6s | %-6s | %-16s |\n", "Имя", "Тип", "Размер", "Кол-во", "Тип компонент");
        printf("----------------------------------------------------------------------------------\n");

        for (int i = 0; i < tableSize; i++) {
            if (table[i].isOccupied) {
                printf("%-5d| %-3d | %-30s | %-12s | %-6d | %-6d | %-16s |\n",
                    table[i].hash,
                    i,
                    table[i].name,
                    table[i].type,
                    table[i].size,
                    table[i].componentCount,
                    table[i].componentType);
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

    int parseLine(const char *line, struct tableElement *elem) {
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
        //стёрли все пробелы в начале и конце строки, а точку с запятой заменили на \0
        char *p = start;

        char typePart1[16] = {0};
        int i = 0;
        while (*p && !is_space((unsigned char)*p) && i < 15) {
            typePart1[i++] = *p++;
        }
        typePart1[i] = '\0';
        //прочитали первое слово в строке

        while (*p && is_space((unsigned char)*p)) p++;//пропускаем пробелы

        char typePart2[16] = {0};
        if (*p && !(*p == '*' || *p == '\0' || *p == '[')) {
            i = 0;
            char *tmp = p;
            while (*tmp && !is_space((unsigned char)*tmp) && *tmp != '*' && *tmp != '[' && *tmp != '=' && i < 15) {
                typePart2[i++] = *tmp++;
            }
            typePart2[i] = '\0';

            if ( (strcmp(typePart1, "unsigned") == 0 && (strcmp(typePart2, "int") == 0 || strcmp(typePart2, "long") == 0)) 
                || (strcmp(typePart1, "long") == 0 && strcmp(typePart2, "double") == 0) ) {
                p = tmp;
            } else {
                typePart2[0] = '\0';
            }
        }//прочитали второе слово, если составной тип

        char baseType[32] = {0};
        strcpy(baseType, typePart1);
        if (typePart2[0]) {
            strcat(baseType, " ");
            strcat(baseType, typePart2);
        }//записываем в одну строку имя типа

        while (*p && is_space((unsigned char)*p)) p++;

        int pointerCount = 0;
        while (*p == '*') {
            pointerCount++;
            p++;
            while (*p && is_space((unsigned char)*p)) p++;
        }
        //посчитали указатели

        char varName[32] = {0};
        i = 0;
        while (*p && *p != '[' && *p != '=' && !is_space((unsigned char)*p) && i < 31) {
            varName[i++] = *p++;
        }
        varName[i] = '\0';
        //прочитали название переменной

        if (strlen(varName) == 0) return 0;//если не получилось прочитать, то пропускаем строку, с ней что-то не так
        strcpy(elem->name, varName);//записываем имя в структуру

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

        if (isArray && componentCount == 0 && *p == '=') {
            p++; // пропускаем '='
            while (*p && is_space((unsigned char)*p)) p++;

            if (*p == '{') {
                p++;
                char *initStart = p;
                char *initEnd = strchr(initStart, '}');
                if (initEnd) {
                    char initContent[256] = {0};
                    int initLen = initEnd - initStart;
                    if (initLen > 0 && initLen < (int)sizeof(initContent)) {
                        strncpy(initContent, initStart, initLen);
                        initContent[initLen] = '\0';
                        int count = 0;
                        char *ptr = initContent;
                        while (*ptr) {
                            if (*ptr == ',') count++;
                            ptr++;
                        }
                        componentCount = (strlen(initContent) > 0) ? count + 1 : 0;
                    }
                }
            }
        }//прочитали фигурные скобки и посчитали число элементов

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
                if (parseLine(line, &elem)) {
                    if (!insert(table, TABLE_SIZE, elem)) {
                        printf("Не удалось добавить элемент %s - таблица заполнена\n", elem.name);
                    }
                } else {
                    printf("Ошибка разбора строки: \"%s\"\n", line);
                }
            }
            fclose(file);
        }

        printTable(table, TABLE_SIZE);

        return result;
    }
