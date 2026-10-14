#include <stdio.h>
const int nmax = 26;

struct queue
{
    int priority;
    char name;
    queue *prev = NULL;
    queue *next = NULL;
};

queue *createList()
{
    queue *person = new queue;
    person->priority = 0;
    person->name = 0;
    person->next = NULL;
    return person;
}

void push(char name, int priority, queue *p)
{
    queue *person = new queue;
    person->priority = priority;
    person->name = name;
    if (p != NULL)
    {
        person->prev = p->prev;
        person->next = p;
        p->prev->next = person;
        p->prev = person;
    }
    else
    {
        p = person;
        p->next = p;
        p->prev = p;
    }
}

void readFile(int *size, int *startposition, int matrixs[nmax][nmax])
{
    char L;
    FILE *fileStream;
    fopen_s(&fileStream, "input1.txt", "r");
    if (fileStream != NULL)
    {
        int i = 0;
        int j = 0;
        fscanf(fileStream, "%d", size);

        fscanf(fileStream, "%s ", &L);
        *startposition = L - 'A';

        for (i = 0; i < *size; i++)
        {
            for (j = 0; j < *size; j++)
            {
                fscanf(fileStream, "%d", &matrixs[i][j]);
            }
        }

        fclose(fileStream);
    }
    else
    {
        printf_s("Error: could not open input.txt\n");
        matrixs = NULL;
    }
}
/* путь, очередь */
// void inputpath(char c, queue *q)
// {
//     person *p = new person;
//     p->elem = c;
//     p->next = NULL;
//     if (q->beg == NULL)
//         q->end = q->beg = p;
//     else
//     {
//         q->end->next = p;
//         q->end = p;
//     }
// }
void findpaths(int matrixs[nmax][nmax], int size, int start, int end, queue *q)
{
    // сделать добавление в очередь с приоритетом начала
    inputpath(start + 'A', q);

    if (start == end)
    {
        // Если конечной вершина, путь в очередь
        inputpath(start + 'A', q);
        return;
    }
    for (int i = 0; i < size; i++)
    {
        if (matrixs[start][i] == 1)
        { // Если есть ребро из start в i
            findpaths(matrixs, size, i, end, q);
        }
    }
}

int main()
{
    int matrixs[nmax][nmax];
    queue *q = NULL;
    int size, end, startname;
    readFile(&size, &startname, matrixs);
    end = size - 1;
    findpaths(matrixs, size, startname, end, q);

    // нет вывода в файл, создание
    printf("%d %d %d %c", size, startname + 1, end, q);

    // int i =0, j=0, n = size;
    // for(i = 0; i < n; i++){ // вывод всего массива
    //     for(j = 0; j < n; j++){
    //         printf_s("%d ", matrixs[i][j]);
    //     }printf("\n");}

    //     for(i = 0, j = 0; i < n; i++){ // вывод столбца
    //         // for(j = 0; j < n; j++){
    //             printf_s("%d ", matrixs[i][j]);
    //        printf("\n");}
}
