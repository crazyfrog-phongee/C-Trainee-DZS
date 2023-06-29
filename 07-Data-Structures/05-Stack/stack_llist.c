#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack_llist.h"

struct llist_node
{
    int data;
    llist_node_t *next;
};

struct llist
{
    llist_node_t *head;
};

llist_t *stack_create(llist_t *stack)
{
    stack = (llist_t *)malloc(sizeof(llist_t));
    stack->head = NULL;

    return stack;
}

void stack_push(llist_t *stack, int data)
{
    assert(NULL != stack);

    llist_node_t *dummy;

    dummy = (llist_node_t *)malloc(sizeof(llist_node_t));
    if (NULL == dummy)
    {
        printf("Can't allocate memory\n");
        exit(EXIT_FAILURE);
    }

    dummy->data = data;
    dummy->next = NULL;

    dummy->next = stack->head;
    stack->head = dummy;
}

void print_stack(const llist_t *stack)
{
    if (NULL == stack)
    {
        printf("Stack no longer exists\n");
        return;
    }
    else if (NULL == stack->head)
    {
        printf("Stack is empty\n");
        return;
    }

    llist_node_t *dummy;

    dummy = stack->head;
    printf("Stack           ||      Top         ||  After Top       ||  Data\n");
    while (NULL != dummy->next)
    {
        printf("%p  ||  %p  ||  %p  ||  %d\n", stack, dummy, dummy->next, dummy->data);
        dummy = dummy->next;
    }
    printf("%p  ||  %p  ||  %p           ||  %d\n", stack, dummy, dummy->next, dummy->data);
}
