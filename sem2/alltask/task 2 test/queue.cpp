#include <stdio.h>
#include <stdlib.h>
#define INPUT "input8.txt"
#define OUTPUT "familytree.txt"
const int nmax = 26;

struct person {
  char name;
  int priority;
};

struct queue {
  person p;
  queue* next;
  queue* prev;
};

void push(queue** head, person p) {
  queue* newNode = new queue;
  newNode->p.name = p.name;
  newNode->p.priority = p.priority;
  
  if (!*head) {
      newNode->next = newNode;
      newNode->prev = newNode;
      *head = newNode;
  } else {
      queue* current = *head;
      while (current->next != *head && current->p.priority <= p.priority) {
          current = current->next;
      }
      
      newNode->next = current;
      newNode->prev = current->prev;
      current->prev->next = newNode;
      current->prev = newNode;
      
      if (p.priority < (*head)->p.priority) {
          *head = newNode;
      }
  }
}

person pop(queue** head) {
  person p = (*head)->p;
  if ((*head)->next == *head) {
      free(*head);
      *head = NULL;
  } else {
      queue* temp = *head;
      (*head)->prev->next = (*head)->next;
      (*head)->next->prev = (*head)->prev;
      *head = (*head)->next;
      free(temp);
  }
  return p;
}

void printQueue(queue** head) {
    queue* temp = NULL;
  person p;
  printf("{");
  while (*head != NULL) {
    p = pop(head);
    push(&temp, p);
    printf(" %c ", p.name);
  }
  while (temp != NULL) {
    p = pop(&temp);
    push(head, p);
  }
  printf("}\n");
}

int readFile(int* size, int* startposition, int matrix[nmax][nmax]) {
  char L;
  FILE* fileStream = fopen(INPUT, "r");
  int result;
  if (fileStream != NULL) {
      int i = 0;
      int j = 0;
      fscanf(fileStream, "%d", size);
      fscanf(fileStream, " %c", &L);
      *startposition = L;
      for (i = 0; i < *size; i++) {
          for (j = 0; j < *size; j++) {
              fscanf(fileStream, "%d", &matrix[i][j]);
          }
      }
      fclose(fileStream);
      result = 1;
  } else {
      printf("Error: could not open input file\n");
      result = 0;
  }
  return result;
}

int pushChildren(queue** head, char name, int matrix[nmax][nmax], int size, int generation) {
  int i = 0;
  int result = 0;
  for (i = 0; i < size; i++) {
    if (matrix[name - 'A'][i] == 1) {
      result = 1;
      push(head, {(char)(i + 'A'), generation});
      printQueue(head);
    }
  }
  return result;
}

int printChildren(int matrix[nmax][nmax], int size, queue** head, int generation, FILE* file) {
  int result = 0;
  person p;
  while (*head != NULL && (*head)->p.priority == generation) {
    result = 1;
    p = pop(head);
    printQueue(head);
    if (generation != 0) fprintf(file, "%c ", p.name);
    pushChildren(head, p.name, matrix, size, generation + 1);
  }
  if (generation != 0) fprintf(file, "\n");
  return result;
}

int main() {
  queue* q = NULL;
  int matrix[nmax][nmax];
  int size = 0;
  int startposition = 0;
  FILE* outputFile = fopen(OUTPUT, "w");
  if (!outputFile) {
      outputFile = fopen(OUTPUT, "w+");
      if (!outputFile) {
          printf("Error: could not create output file\n");
      }
  }
  else{int result = readFile(&size, &startposition, matrix);
  if (result == 1) {
    push(&q, {(char)startposition, 0});
    printQueue(&q);
    int generation = 0;
    while (q != NULL) {
      printChildren(matrix, size, &q, generation, outputFile);
      if (q != NULL && generation != q->p.priority) generation = q->p.priority;
    }
  }
  fclose(outputFile);
  }
  return 0;
}
