#include <stdio.h>

#include "stack_llist.h"

static llist_t *stack;

int main(int argc, char const *argv[])
{
    stack = stack_create(stack);
    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);
    print_stack(stack);

    return 0;
}
