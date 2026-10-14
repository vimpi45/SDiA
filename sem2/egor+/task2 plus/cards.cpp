#include <stdio.h>
#include <stdlib.h>
// 3 пз+ стр 86 вариант 7б картинка б
#define INPUT "input3.txt"
#define OUTPUT "cards.txt"
struct list
{
    int elem;
    list *next;
};
typedef list stack;

stack *push(int elem, stack *s)
{
    stack *p = new stack;
    p->elem = elem;
    p->next = s;
    return p;
}

stack *pop(int *c, stack *s)
{
    stack *p = s;
    *c = s->elem;
    s = s->next;
    delete p;
    return s;
}

int readFile(int *size, stack **up, stack **down)
{
    int L, elem, i, k, g;
    
    stack *srep = NULL;
    FILE *fileStream = fopen(INPUT, "r");
    int result;
    if (fileStream != NULL)
    {
        // fscanf(fileStream, " %c", &L);
        // *startposition = L;
        int delimiter = ' ';
        fscanf_s(fileStream, " %d", &L);
        *size = L;
        k = L / 2;
        g = L - k;
        stack *upreplace = NULL;
        for (i = 0; i < k; i++)
        {
            fscanf_s(fileStream, " %d", &elem);
            *down = push(elem, *down);
        }
        for (i = 0; i < g; i++)
        {
            fscanf_s(fileStream, " %d", &elem);
            upreplace = push(elem, upreplace);
        }
        for (i = 0; i < g; i++)
        {
            upreplace = pop(&elem, upreplace);
            *up = push(elem, *up);
        }
        fclose(fileStream);
        result = 1;
    }
    else
    {
        printf("Error: could not open input file\n");
        result = 0;
    }
    return result;
}
void getback(stack **s, stack **up, stack **down, int size)
{
    int i, elem1, elem2;
    if (size % 2 == 0)
        for (i = 0; i < (size / 2); i++)
        {
            *up = pop(&elem1, *up);
            *s = push(elem1, *s);
            *down = pop(&elem2, *down);
            *s = push(elem2, *s);
        }
    else
    {
        for (i = 0; i < (size / 2); i++)
        {
            *up = pop(&elem1, *up);
            *s = push(elem1, *s);
            *down = pop(&elem2, *down);
            *s = push(elem2, *s);
        }
        *up = pop(&elem1, *up);
        *s = push(elem1, *s);
    }
}
void printfile(stack *s, FILE *file, int size)
{
    int i, elem;
    for (i = 0; i<size; i++){
        s = pop(&elem, s);
        fprintf(file, "%d ", elem);
    }
    fprintf(file, "<== 1 элемент стека");
}
int main()
{
    stack *s = NULL;
    stack *up = NULL;
    stack *down = NULL;
    int size = 0;
    FILE *outputFile = fopen(OUTPUT, "w");
    if (!outputFile)
    {
        outputFile = fopen(OUTPUT, "w+");
        if (!outputFile)
        {
            printf("Error: could not create output file\n");
            return 1;
        }
    }

    int result = readFile(&size, &up, &down);
    if (result == 1)
    {
        getback(&s, &up, &down, size);
        printfile(s, outputFile, size);
    }
    fclose(outputFile);
    return 0;
}
