#include <stdio.h>

#include "stack_llist.h"

static llist_t *stack;
static llist_t *reverse_stack;

int main(int argc, char const *argv[])
{
    stack = stack_create(stack);
    reverse_stack = stack_create(stack);
    
    for (int i = 0; i < 100;)
    {
        stack_push(stack, i);
        i = i + 5;
        print_stack(stack);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("Value popping: %d\n", stack_pop(stack));
    }

    printf("\nAfter popping:\n");
    print_stack(stack);

    printf("\nCurrent value of the top element of stack: %d\n", stack_peek(stack));

    int val_popping;
    int current_size;

    current_size = stack_size(stack);
    for (int i = 0; i < current_size; i++)
    {   
        val_popping = stack_pop(stack);
        stack_push(reverse_stack, val_popping);
    }

    print_stack(reverse_stack);

    stack_free(stack);
    stack_free(reverse_stack);
    
    return 0;
}
