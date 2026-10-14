#include <stdio.h>
#include <stdlib.h>
#define INPUT "input7.txt"
#define OUTPUT "familytree.txt"
const int nmax = 26;
// вывод доделать, обычными операциями. мой 5л пз+2 стр 656. 3а пз+1 стр 40
typedef struct queue
{
  char name;
  int priority;
  struct queue *next;
  struct queue *prev;
} queue;

void printQueue(queue* q){
  printf("{ ");
  queue* temp  = q;
  if (q != NULL) {
    printf("%c ", q->name);
    q=q->next;
    while (q!= temp)
    {
      printf("%c ", q->name);
    q = q->next;
    }
}
  printf("}\n");
}

void push(queue **head, char name, int priority)
{
  queue *newNode = new queue;
  newNode->name = name;
  newNode->priority = priority;

  if (!*head)
  {
    newNode->next = newNode;
    newNode->prev = newNode;
    *head = newNode;
  }
  else
  {
    queue *current = *head;
    while (current->next != *head && current->priority <= priority)
    {
      current = current->next;
    }

    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;

    if (priority < (*head)->priority)
    {
      *head = newNode;
    }
  }
  printQueue(*head);
}

char pop(queue **head)
{
  char name = (*head)->name;
  if ((*head)->next == *head)
  {
    free (*head);
    *head = NULL;
  }
  else
  {
    queue *temp = *head;
    (*head)->prev->next = (*head)->next;
    (*head)->next->prev = (*head)->prev;
    *head = (*head)->next;
    free (temp);
  }
  printQueue(*head);
  return name;
}

int readFile(int *size, int *startposition, int matrix[nmax][nmax])
{
  char L;
  FILE *fileStream = fopen(INPUT, "r");
  int result;
  if (fileStream != NULL)
  {
    int i = 0;
    int j = 0;
    fscanf(fileStream, "%d", size);
    fscanf(fileStream, " %c", &L);
    *startposition = L;
    for (i = 0; i < *size; i++)
    {
      for (j = 0; j < *size; j++)
      {
        fscanf(fileStream, "%d", &matrix[i][j]);
      }
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

int pushChildren(queue **head, char name, int matrix[nmax][nmax], int size, int generation)
{
  int i = 0;
  int result = 0;
  for (i = 0; i < size; i++)
  {
    if (matrix[name - 'A'][i] == 1)
    {
      result = 1;
      push(head, i + 'A', generation);
    }
  }
  return result;
}

int printChildren(int matrix[nmax][nmax], int size, queue **head, int generation, FILE *file)
{
  int result = 0;
  char name;
  while (*head != NULL && (*head)->priority == generation)
  {
    result = 1;
    name = pop(head);  
    if (generation != 0)
      fprintf(file, "%c ", name);
    pushChildren(head, name, matrix, size, generation + 1);
  }
  if (generation != 0)
    fprintf(file, "\n");
  return result;
}


int main()
{
  queue *q = NULL;
  int matrix[nmax][nmax];
  int size = 0;
  int startposition = 0;
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
  int result = readFile(&size, &startposition, matrix);
  if (result == 1)
  {
    push(&q, startposition, 0);
    int generation = 0;
    while (q != NULL)
    {
      printChildren(matrix, size, &q, generation, outputFile);
      if (q != NULL && generation != q->priority)
        generation = q->priority;
    }
  }
  fclose(outputFile);
  return 0;
}
