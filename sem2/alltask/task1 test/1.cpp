#include <stdio.h>
struct ListNode {
    int degree;
    float coefficient;

    ListNode* next;
};

ListNode* createList() {
    ListNode* list = new ListNode;
    list->degree = 0;
    list->coefficient = 0;
    list->next = NULL;
    return list;
}

// void insertAfter(ListNode* position, int degree, float coefficient) {
//     ListNode* tempNode = new ListNode;
//     tempNode->degree = degree;
//     tempNode->coefficient = coefficient;
//     tempNode->next = position->next;
//     position->next = tempNode;
// }

void mergeAfter(ListNode* position, ListNode* other) {
    ListNode* originalNext = position->next;
    while (other != NULL) {
        ListNode* tempNode = new ListNode;
        tempNode->degree = other->degree;
        tempNode->coefficient = other->coefficient;
        tempNode->next = position->next;
        position->next = tempNode;
        // insertAfter(position, other->degree, other->coefficient);
        position = position->next;
        other = other->next;
    }
    position->next = originalNext;
}

ListNode* readPolynomial(FILE* fileStream) {
    ListNode* list = new ListNode;
    int degree, delimiter, iii;
    float coefficient;
    delimiter = fscanf_s(fileStream, "%fa%d", &coefficient, &degree);
    list->degree = degree;
    list->coefficient = coefficient;
    list->next = NULL;
    // float delimiter,iii = fscanf_s(fileStream, "%fa%d", &coefficient, &degree);
    
    ListNode* end = list;
    delimiter = ' ';
    while (coefficient != 0 && degree != 0 && delimiter != EOF) {       // && delimiter != EOF 
        delimiter = fscanf_s(fileStream, "%fa%d", &coefficient, &degree);
        if (coefficient != 0 && delimiter != EOF){
        ListNode* tempNode = new ListNode;
        tempNode->degree = degree;
        tempNode->coefficient = coefficient;
        tempNode->next = end->next;
        end->next = tempNode;
        // insertAfter(end, degree, coefficient);
        end = end->next;
        // delimiter = fscanf_s(fileStream, "%fa%d", &coefficient, &degree);
        // delimiter = fgetc(fileStream);
        }
    }

    return list;
}

void readInput(ListNode** outP, ListNode** outQ) {
    FILE* fileStream;
    fopen_s(&fileStream, "input1.txt", "r");
    if (fileStream != NULL) {
        *outP = readPolynomial(fileStream);
        *outQ = readPolynomial(fileStream);
        fclose(fileStream);
    }
    else {
        printf_s("Error: could not open input.txt\n");
        *outP = NULL;
        *outQ = NULL;
    }
}

void printOutput(ListNode* result) {
    FILE* fileStream;
    fopen_s(&fileStream, "output.txt", "w");
    if (fileStream != NULL) {
        ListNode* current = result->next;
        while (current) {
            fprintf_s(fileStream, "%fa%d ", current->coefficient, current->degree);
            current = current->next;
        }

        fclose(fileStream);
    }
    else {
        printf_s("Error: could not open output.txt");
    }
}

ListNode* sumPolynomials(ListNode* p, ListNode* q) {
    ListNode* result = new ListNode;
    result->degree = 0;
    result->coefficient = 0;
    result->next = NULL;
    ListNode* end = result;

    while (p != NULL && q != NULL) {
        if (p->degree > q->degree) {
            // insertAfter(end, p->degree, p->coefficient);
            ListNode* tempNode = new ListNode;

            tempNode->degree = p->degree;
            tempNode->coefficient = p->coefficient;
            tempNode->next = end->next;
            end->next = tempNode;
            end = end->next;
            p = p->next;
        }
        else if (p->degree < q->degree) {
            // insertAfter(end, q->degree, q->coefficient);
            ListNode* tempNode = new ListNode;
           
            tempNode->degree = q->degree;
            tempNode->coefficient = q->coefficient;
            tempNode->next = end->next;
            end->next = tempNode;
            end = end->next;
            q = q->next;
        }
        else {
            float coefficientSum = p->coefficient + q->coefficient;
            if (coefficientSum != 0) {
                // insertAfter(end, q->degree, coefficientSum);
                ListNode* tempNode = new ListNode;
                
                tempNode->degree = q->degree;
                tempNode->coefficient = coefficientSum;
                tempNode->next = end->next;
                end->next = tempNode;

                end = end->next;
            }
            p = p->next;
            q = q->next;
        }
        
    }
    if (p != NULL)
    mergeAfter(end, p);
    if(q != NULL) //else
    mergeAfter(end, q);
    
    return result;
}

int main() {
    ListNode* p = NULL;
    ListNode* q = NULL;
    readInput(&p, &q);

    if (p != NULL && q != NULL) {
        ListNode* result = sumPolynomials(p, q);
        printOutput(result);
    }

    return 0;
}
