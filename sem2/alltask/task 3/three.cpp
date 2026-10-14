#include <stdio.h>
#include <stdlib.h>
#define INPUT "input9.txt"
struct tree
{
    char elem;
    tree *left, *right;
};
struct list
{
    tree *elem;
    list *next;
};typedef list stack;
stack *push(tree *c, stack *s)
{
    stack *p = new stack;
    p->elem = c;
    p->next = s;
    return p;
}

int pop(tree **c, stack **s)
{
    if (*s)
    {
        stack *p = *s;
        *c = (*s)->elem;
        *s = (*s)->next;
        delete p;
        return 1;
    }
    return 0;
}
stack* copy_stack(stack* original) {
    stack* new_stack = NULL; 
    stack* temp_stack = NULL; 
    tree* elem;
    while (original != NULL) {
        pop(&elem, &original);       
        temp_stack = push(elem, temp_stack); 
    }

    while (temp_stack != NULL) {
        pop(&elem, &temp_stack);    
        original = push(elem, original); 
        new_stack = push(elem, new_stack); 
    }
    return new_stack;
}
int findtree(tree *v, stack* h)
{
    char x = v->elem;
    int f = 0, c = 0;
    while (v != NULL && !f) 
    { 
       if (v->elem == x && c > 0) 
            f = 1; 
       else 
       {
          if (v->left != NULL && v->right != NULL) 
          { 
            h = push(v->right, h); 
            v = v->left; 
          }
          else 
             if (v->left == NULL && v->right == NULL) 
             { 
                if (h != NULL){
                    pop(&v, &h);
                }else{
                    v = NULL;
                }
             } 
             else 
                v = v->left != NULL ? 
                   v->left : v->right; 
       } 
       c++;
    } 
    return f;
}
int dfs(tree* t)
{
    int f = 0;
    stack *s = NULL;
    stack *n = NULL;
    while (t != NULL && !f)
    {
        f = findtree(t, n);
        if (t->left != NULL && t->right != NULL)
        {
            s = push(t->right, s);
            t = t->left;
        }
        else if (t->left == NULL && t->right == NULL)
        {
            if (s != NULL){
                pop(&t, &s);
            }else{
                t = NULL;
            }
        }
        else
            t = t->left != NULL ? t->left : t->right;
        n = copy_stack(s);
    }
    return f;
}
tree *BuildTree(FILE *file)
{
    char c = 0;
    fscanf(file, " %c", &c);
    switch (c)
    {
    case '(':
    {
        tree *t = new tree;
        fscanf(file, " %c", &c);
        t->elem = c;
        t->left = BuildTree(file);
        t->right = BuildTree(file);
        fscanf(file, " %c", &c);
        return t;
    }
    case ',':
        return BuildTree(file);
    case '0':
        return NULL;
    default:
        return NULL;
    }
}
int main()
{
    FILE *file = fopen(INPUT, "r");
    if (file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }
    tree *t = BuildTree(file);

    fclose(file);
    if (dfs(t))
        printf("Есть хотя-бы 2 повторяющихся элемента");
    else
        printf("Нет хотя-бы двух повторяющихся элементов");
    return 0;
}
