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

int is_empty_stack(const llist_t *stack)
{
    assert(NULL != stack);

    if (NULL == stack->head) /* If Stack is empty */
    {
        return 1;
    }
    /* If Stack is not empty */
    return 0;
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

int stack_pop(llist_t *stack)
{
    assert(NULL != stack);

    if (1 == is_empty_stack(stack))
    {
        printf("Stack is empty\n");
        return STACK_EMPTY;
    }

    llist_node_t *dummy;
    int ret_val;

    dummy = stack->head;
    ret_val = stack->head->data;
    stack->head = stack->head->next;
    
    free(dummy);
    dummy = NULL;

    return ret_val;
}

int stack_peek(const llist_t *stack)
{
    assert(NULL != stack);

    if (1 == is_empty_stack(stack))
    {
        printf("Stack is empty\n");
        return STACK_EMPTY;
    }

    return stack->head->data;
}

int stack_size(const llist_t *stack)
{
    assert(NULL != stack);

    if (1 == is_empty_stack(stack))
    {
        return 0;
    }

    llist_node_t *dummy;
    int size = 0;

    dummy = stack->head;

    while (NULL != dummy)
    {
        size++;
        dummy = dummy->next;
    }

    return size;
}

void stack_free(llist_t *stack)
{
    assert(NULL != stack);

    while (NULL != stack->head)
    {
        stack_pop(stack);
    }

    free(stack);
    stack = NULL;
}

void print_stack(const llist_t *stack)
{
    if (NULL == stack)
    {
        printf("Stack no longer exists\n");
        return;
    }
    else if (1 == is_empty_stack(stack))
    {
        printf("Stack is empty\n");
        return;
    }

    llist_node_t *dummy;
    int index_of_element = stack_size(stack) - 1;

    dummy = stack->head;
    // printf("Stack has %d elements\n", stack_size(stack));
    printf("\n##### Printing STACK Content Summary #####\n");
    printf("Stack           ||Address of Element||  Element    ||  Data\n");

    while (NULL != dummy->next)
    {

        printf("%p  ||  %p  ||  %d          ||  %d\n", stack, dummy, index_of_element--, dummy->data);
        dummy = dummy->next;
    }
    printf("%p  ||  %p  ||  %d          ||  %d\n", stack, dummy, index_of_element, dummy->data);

    return;
}
