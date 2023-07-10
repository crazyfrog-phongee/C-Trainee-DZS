#include <stdio.h>
#include <string.h>

#include "stack_arr.h"

int init_stack(stack_t *s)
{
    memset(s->stack, 0, STACK_SIZE - 1);
    s->top = -1;

    return STACK_SUCCESS;
}

int is_full_stack(const stack_t *s)
{
    if (s->top == (STACK_SIZE - 1)) /* If Stack is full */
    {
        return 1;
    }
    /* If Stack is not full */
    return 0;
}

int is_empty_stack(const stack_t *s)
{
    if (s->top == -1) /* If Stack is empty */
    {
        return 1;
    }
    /* If Stack is not empty */
    return 0;
}

int stack_push(stack_t *s, int data)
{
    if (1 == is_full_stack(s))
    {
        printf("Stack overflow\n");
        return -1;
    }

    s->top++;
    s->stack[s->top] = data;

    return STACK_SUCCESS;
}

int stack_pop(stack_t *s)
{
    int ret_val;

    if (1 == is_empty_stack(s))
    {
        printf("Stack underflow\n");
        return -1;
    }
    ret_val = s->stack[s->top];
    s->top--;

    return ret_val;
}

int stack_peek(const stack_t *s)
{
    if (1 == is_empty_stack(s))
    {
        printf("Stack underflow\n");
        return -1;
    }

    return s->stack[s->top];
}

void print_stack(const stack_t *s)
{
    printf("\n##### Printing STACK Content Summary #####\n");
    for (int i = 0; i <= s->top; i++)
    {
        printf("%d ", s->stack[i]);
    }
    printf("\n");

    return;
}
