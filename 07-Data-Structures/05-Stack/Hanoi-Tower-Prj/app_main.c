#include <stdio.h>
#include <string.h>

#include "lib/stack_llist.h"

static llist_t *peg[3];

int main(int argc, char const *argv[])
{
    int num_disks, from_peg, to_peg;
    int value = 0;

    for (int i = 0; i < 3; i++)
    {
        peg[i] = stack_create(peg[i]);
    }
    
    printf("Enter number of disks:");
    scanf("%d", &num_disks);

    for (int j = num_disks - 1; j >= 0 ; j--)
    {
        stack_push(peg[0], j);
    }

    printf("\n=====Before starting algorithm=====\n");
    for (int i = 0; i < 3; i++)
    {
        print_stack(peg[i]);
    }

    printf("\n=====On starting algorithm=====\n");
    for (int k = 1; k < (1 << num_disks); k++)
    {
        from_peg = (k & (k - 1)) % 3;
        to_peg = ((k | (k - 1)) + 1) % 3;
        printf("Move %dth, from peg %d to peg %d\n", k, from_peg, to_peg);

        switch (from_peg)
        {
            case 0:
                value = stack_pop(peg[0]);
                break;
            case 1:
                value = stack_pop(peg[1]);
                break;
            case 2:
                value = stack_pop(peg[2]);
                break;
        }

        switch (to_peg)
        {
            case 0:
                stack_push(peg[0], value);
                break;
            case 1:
                stack_push(peg[1], value);
                break;
            case 2:
                stack_push(peg[2], value);
                break;
        }

        for (int i = 0; i < 3; i++)
        {
            print_stack(peg[i]);
        }

        printf("\n\n\n");
    }

    /* De-allocation memory */
    for (int i = 0; i < 3; i++)
    {
        stack_free(peg[i]);
    }

    return 0;
}
