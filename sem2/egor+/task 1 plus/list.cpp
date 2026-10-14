#include <stdio.h>
#include <stdlib.h>
#define INPUT "input1.txt"
#define OUTPUT "output.txt"
struct list
{
    float elem;
    list *next = NULL, *prev = NULL;
};

int typesort(list *current)
{
    int b = 3;
    if (current->next != NULL)
    {
        if (current->elem > current->next->elem)
            b = 0;
        if (current->elem < current->next->elem)
            b = 1;
        if (current->elem == current->next->elem)
            b = 2;
    }
    return b;
}

list *readlist(FILE *fileStream)
{
    list *l = new list;
    l->next = NULL;
    int delimiter;
    float elem;
    delimiter = fscanf_s(fileStream, "%f", &elem);
    delimiter = fgetc(fileStream);
    l->elem = elem;
    l->next = NULL;
    list *end = l;
    while (delimiter != EOF && delimiter != '\n')
    {
        delimiter = fscanf_s(fileStream, "%f", &elem);
        delimiter = fgetc(fileStream);
        // if(delimiter != EOF && delimiter != '\n'){
        list *newNode = new list;
        newNode->elem = elem;
        newNode->next = NULL;
        newNode->prev = end;
        if (l == NULL)
        {
            l = newNode;
            end = newNode;
        }
        else
        {
            end->next = newNode;
            end = newNode;
        }
    // } 
    }
    return l;
}
int del2(list **l, int k)
{
    list *current = *l;
    int index = 0;
    while (index < k)
    {
        current = current->next;
        index++;
    }
    if (current->prev == NULL)
    {
        *l = current->next;
        if (*l != NULL)
        {
            (*l)->prev = NULL;
        }
    }
    else
    {
        current->prev->next = current->next;
        if (current->next != NULL)
            current->next->prev = current->prev;
    }

    return 1;
}
int isSorted(list *l, int b)
{
    list *current = l;

    while (current -> next != NULL)
    {
        float g = current->next->elem;
        float c = current->elem;
        if (b == 0)
            if (c <= g)
                return 0;
        if (b == 1)
            if (c >= g)
                
                return 0;
        if (b == 2)
            if (c != g)
                return 0;
        current = current->next;
    }
    return 1;
}

void insertSorted(list **l, float p, int b)
{
    list *newNode = new list;
    newNode->elem = p;
    newNode->next = NULL;
    newNode->prev = NULL;

    list *current = *l;
    if (b != 0)
    {
        if (p <= current->elem)
        {
            newNode->next = current;
            current->prev = newNode;
            *l = newNode;
            return;
        }
        while (current->next != NULL && current->next->elem < p)
            current = current->next;

        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != NULL)
            current->next->prev = newNode;
        current->next = newNode;
    }
    else
    {
        if (p >= current->elem)
        {
            newNode->next = current;
            current->prev = newNode;
            *l = newNode;
            return;
        }
        while (current->next != NULL && current->next->elem > p)
            current = current->next;

        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != NULL)
            current->next->prev = newNode;
        current->next = newNode;
    }
}

void printOutput(list *result)
{
    FILE *fileStream;
    fopen_s(&fileStream, "output.txt", "w");
    if (fileStream != NULL)
    {
        list *current = result;
        while (current)
        {
            fprintf_s(fileStream, "%f ", current->elem);
            current = current->next;
        }

        fclose(fileStream);
    }
    else
    {
        printf_s("Error: could not open output.txt");
    }
}
int main()
{
    float p;
    int k;
    list *l = new list;
    l->next = NULL;
    FILE *fileStream;
    fopen_s(&fileStream, "input1.txt", "r");
    if (fileStream != NULL)
    {
        l = readlist(fileStream);
        fscanf_s(fileStream, "%f %d", &p, &k);
        // fscanf_s(fileStream, "%d", k);
        fclose(fileStream);
    }
    else
    {
        printf_s("Error: could not open input.txt\n");
        l = NULL;
    }
    int b = typesort(l);
    if (isSorted(l, b))
        insertSorted(&l, p, b);
    else
        del2(&l, k - 1);

    printOutput(l);
}
