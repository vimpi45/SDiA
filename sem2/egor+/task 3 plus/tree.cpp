#include <stdio.h>
#include <stdlib.h>
// 3 пз+ стр 86 вариант 7б картинка б
struct tree
{
    int elem;
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
tree* createTreeNode(int value) {
    tree *node = new tree;
    node->elem = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Построение дерева с использованием стека
tree* buildTree(int n) {
    if (n < 1) {
        return NULL;
    }

    stack *s = NULL;
    tree* t = createTreeNode(1);
    s = push(t, s);

    while (s != NULL) {
        tree* currentNode;
        pop(&currentNode, &s);

        if (currentNode->elem < n) {
                       
            currentNode->left = createTreeNode(currentNode->elem + 1);
            currentNode->right = createTreeNode(currentNode->elem + 1);

            s = push(currentNode->right, s);
            s = push(currentNode->left, s);
        }
    }

    return t;
}

void dfs(tree* t)
{
    stack *s = NULL;
    stack *n = NULL;
    int k = 0;
    while (t != NULL)
    {
        // for (int i = 0; i < k; i++) 
        //     printf("    ");
        
        printf("%d ", t->elem);
        if (t->left != NULL && t->right != NULL)
        {
            s = push(t->right, s);
            t = t->left;
            // k++;
            // printf("\n");
            // printf("%d ", t->elem);
        }
        else if (t->left == NULL && t->right == NULL)
        {
            if (s != NULL){
                pop(&t, &s);
        
                // k--;
                printf("\n");
                // printf("%d ", t->elem);
            }else
                
                t = NULL;
            
        }
        else{
            
            t = t->left != NULL ? t->left : t->right;
            
        }
    }
}
int main(){
    int n;
    scanf_s("%d", &n);
    tree* t = buildTree(n);
    dfs(t);

}