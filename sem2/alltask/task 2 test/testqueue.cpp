#include <stdio.h>
#include <stdlib.h>

// struct queue {
//     int data;
//     struct queue* next;
//     struct queue* prev;
// };
struct list
{
    char elem = 0;
    list *next = NULL;
};
struct queue
{
    list *beg = NULL, *end = NULL;
};
// struct queue* createqueue(int x) {
//     struct queue* newqueue = (struct queue*)malloc(sizeof(struct queue));
//     newqueue->data = x;
//     newqueue->next = newqueue->prev = NULL;
//     return newqueue;
// }
// struct queue* insertAtEnd(struct queue* head, int newData) {
//     struct queue* newqueue = createqueue(newData);
    
//     if (!head) {
      
//         // List is empty
//         newqueue->next = newqueue->prev = newqueue;
//         head = newqueue;
//     } else {
      
//         // List is not empty
//         struct queue* last = head->prev; 
        
//         // Insert new node at the end
//         newqueue->next = head;
//         newqueue->prev = last;
//         last->next = newqueue;
//         head->prev = newqueue;
//     }
    
//     return head;
// }
void push(struct queue *q, char c)
{
    list *p = new list;
    p->elem = c;
    p->next = NULL;
    if (q->beg == NULL)
    q->end = q->beg = p;
    else
    {
    q->end->next = p;
    q->end = p;
 }
}
int main(){
    queue* beg;
    // queue *beg = NULL; 
    char c = 'A';
    push(beg,c);
    printf("%c", beg);


}