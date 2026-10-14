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
};
typedef list stack;

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
int findtree(tree *t, char x, stack* s)
{
    int f = 0, c = 0;
    while (t != NULL && !f)
    {
        if (t->elem == x)
            c++;
        if (c>=2)
            f = 1;
        else
        {
            if (t->left != NULL && t->right != NULL)
            {
                s = push(t->right, s);
                t = t->left;
            }
            else if (t->left == NULL && t->right == NULL)
            {
                if (!pop(&t, &s))
                    t = NULL;
            }
            else
                t = t->left != NULL ? t->left : t->right;
        }      
    }
    return f;
}

// int pop(tree **c, stack **s) 
// { 
//     stack *p = *s;
//     *c = (*s)->elem;
//     *s = (*s)->next;
//     delete s;
// }


int dfs(tree* t)
{
    stack* copy = NULL;
    int f = 0, c = 0;
    stack *s = NULL;
    while (t != NULL && !f)
    {  
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
                // copy = s;
                t = NULL;
            }
        }
        else
            t = t->left != NULL ? t->left : t->right;
        
        // tree* node = t;
        // while (node != NULL && !f)
        // {   
        //     if (t->elem == node->elem)
        //         c++;
        //     if (c>=2)
        //         f = 1;
        //     else{
        //     if(node->left != NULL && node->right != NULL)
        //     {
        //         copy = push(node->right, copy);
        //         node = node->left;
        //     }
        //     else if (node->left == NULL && node->right == NULL)
        //     {
        //         if (copy != NULL){
        //             pop(&node, &copy);
        //         }else
        //         node = NULL;
                    
        //     }
        //     else
        //     node = node->left != NULL ? node->left : node->right;
        // }
        // }
        // t = node;
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
        return 0;
    }
    tree *t = BuildTree(file);

    fclose(file);
    if (dfs(t))
        printf("Есть хотя-бы 2 повторяющихся элемента");
    else
        printf("Нет хотя-бы двух повторяющихся элементов");
    return 0;
}
