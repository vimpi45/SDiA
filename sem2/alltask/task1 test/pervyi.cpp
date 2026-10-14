#include <stdio.h>

struct ListNode
{
    int degree;
    float coefficient;

    ListNode *next;
};

ListNode *createList()
{
    ListNode *list = new ListNode;
    list->degree = 0;
    list->coefficient = 0;
    list->next = NULL;
    return list;
}

void insertAfter(ListNode *position, int degree, float coefficient)
{
    ListNode *tempNode = new ListNode;
    tempNode->degree = degree;
    tempNode->coefficient = coefficient;
    tempNode->next = position->next;
    position->next = tempNode;
}

void mergeAfter(ListNode *position, ListNode *other)
{
    ListNode *originalNext = position->next;
    while (other != NULL)
    {
        insertAfter(position, other->degree, other->coefficient);
        position = position->next;
        other = other->next;
    }
    position->next = originalNext;
}

ListNode *readPolynomial(FILE *fileStream)
{
    ListNode *result = createList();
    ListNode *end = result;
    int degree;
    float coefficient;
    int delimiter = ' ';
    while (delimiter != EOF && delimiter != '\n')
    {
        fscanf_s(fileStream, "%fa%d", &coefficient, &degree);
        insertAfter(end, degree, coefficient);
        end = end->next;
        delimiter = fgetc(fileStream);
    }

    return result;
}

void readInput(ListNode **outP, ListNode **outQ)
{
    FILE *fileStream;
    fopen_s(&fileStream, "..\\input.txt", "r");
    if (fileStream != NULL)
    {
        *outP = readPolynomial(fileStream);
        *outQ = readPolynomial(fileStream);
        fclose(fileStream);
    }
    else
    {
        printf_s("Error: could not open input.txt\n");
        *outP = NULL;
        *outQ = NULL;
    }
}

void printOutput(ListNode *result)
{
    FILE *fileStream;
    fopen_s(&fileStream, "..\\output.txt", "w");
    if (fileStream != NULL)
    {
        ListNode *current = result->next;
        while (current)
        {
            fprintf_s(fileStream, "%fa%d ", current->coefficient, current->degree);
            current = current->next;
        }

        fclose(fileStream);
    }
    else
    {
        printf_s("Error: could not open output.txt");
    }
}

ListNode *sumPolynomials(ListNode *p, ListNode *q)
{
    ListNode *result = createList();
    ListNode *end = result;

    p = p->next; // Skip fictive node
    q = q->next;

    while (p != NULL && q != NULL)
    {
        if (p->degree > q->degree)
        {
            insertAfter(end, p->degree, p->coefficient);
            p = p->next;
        }
        else if (p->degree < q->degree)
        {
            insertAfter(end, q->degree, q->coefficient);
            q = q->next;
        }
        else
        {
            float coefficientSum = p->coefficient + q->coefficient;
            if (coefficientSum != 0)
            {
                insertAfter(end, q->degree, coefficientSum);
            }
            p = p->next;
            q = q->next;
        }
        end = end->next;
    }
    mergeAfter(end, p);
    mergeAfter(end, q);

    return result;
}

int main()
{
    ListNode *p = NULL;
    ListNode *q = NULL;
    readInput(&p, &q);

    if (p != NULL && q != NULL)
    {
        ListNode *result = sumPolynomials(p, q);
        printOutput(result);
    }

    return 0;
}
