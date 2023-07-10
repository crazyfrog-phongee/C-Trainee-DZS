#include <stdio.h>
#include <stdlib.h>

#include "stack_arr.h"

int main(int argc, char const *argv[])
{
    stack_t my_stack;
    int val_pop;
    
    init_stack(&my_stack);

    /* Pushing data to stack */
    for (int i = 0; i < 40;)
    {
        stack_push(&my_stack, i);
        i = i + 3;
    }

    /* Before popping */
    print_stack(&my_stack);

    val_pop = stack_pop(&my_stack);
    printf("Value popping: %d\n", val_pop);

    /* After popping */
    print_stack(&my_stack);

    return 0;
}