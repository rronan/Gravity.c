// C program for linked list implementation of stack
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Space;
 
struct Stack {
    struct Space* data;
    struct Stack* next;
};
 
struct Stack* newStack(struct Space* data)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->data = data;
    stack->next = NULL;
    return stack;
}
 
int isEmpty(struct Stack* root)
{
    return !root;
}
 
struct Stack* push(struct Stack** root, struct Space* data)
{
    if (!root) return newStack(data);
    struct Stack* stack = newStack(data);
    stack->next = *root;
    return stack;
}
 
struct Space* pop(struct Stack** root)
{
    if (isEmpty(*root))
        return NULL;
    struct Stack* temp = *root;
    *root = (*root)->next;
    struct Space* popped = temp->data;
    free(temp);
 
    return popped;
}
 
struct Space* peek(struct Stack* root) {
    if (isEmpty(root))
        return NULL;
    return root->data;
}
