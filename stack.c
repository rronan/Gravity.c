// C program for linked list implementation of stack
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
 
struct Variable;

struct Stack {
    struct Variable* data;
    struct Stack* next;
};
 
struct Stack* newStack(struct Variable* data)
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
 
void push(struct Stack** root, struct Variable* data)
{
    struct Stack* stack = newStack(data);
    stack->next = *root;
    *root = stack;
}
 
struct Variable* pop(struct Stack** root)
{
    if (isEmpty(*root))
        return NULL;
    struct Stack* temp = *root;
    *root = (*root)->next;
    struct Variable* popped = temp->data;
    free(temp);
 
    return popped;
}
 
struct Variable* peek(struct Stack* root)
{
    if (isEmpty(root))
        return NULL;
    return root->data;
}
