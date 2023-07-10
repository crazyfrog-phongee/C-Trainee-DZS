#include <stdio.h>

#include "user_app.h"

static void display_starting(const stack_t *peg)
{
    display_pegs(peg);
    printf("\nGame: Tower of Hanoi\n");
    printf("Objective: Your goal is to insert the numbers into the third pole such that from top to bottom, they are in ascending order\n");
    printf("Rule: You cannot put an greater number above a smaller number at any point in the game\n");
    printf("Good luck!\n");

    return;
}

void init_game(stack_t *peg)
{
    for (int i = 0; i < NUM_PEGS; i++)
    {
        init_stack(&peg[i]);
    }

    for (int j = STACK_SIZE; j >= 1; j--)
    {
        stack_push(&peg[0], j);
    }

    display_starting(peg);

    return;
}

static void display_level(const stack_t *peg, int level)
{
    for (int i = 0; i < NUM_PEGS; i++)
    {
        if (peg[i].stack[level] == 99 || peg[i].stack[level] == 0)
        {
            printf(" [ ]\t");
        }
        else
        {
            printf(" [%d]\t", peg[i].stack[level]);
        }
    }
    printf("\n");
}

void display_pegs(const stack_t *peg)
{
    for (int i = STACK_SIZE - 1; i >= 0; i--)
    {
        display_level(peg, i);
    }

    for (int i = 0; i < NUM_PEGS; i++)
    {
        printf("Peg %d\t", i);
    }
    
    printf("\n");
    
    return;
}

int user_pop(stack_t *peg)
{
    int popping_peg, popping_value;

choose_where_to_pop:
    while (1)
    {
        printf("Choose peg to pop from: ");
        if (scanf("%d", &popping_peg) < 1)
        {
            getchar();
            printf("You entered a non - numeric value, try again\n");
            continue;
        }

        if (popping_peg > (NUM_PEGS - 1) || popping_peg < 0)
        {
            printf("You entered a unvalid number, try again\n");
        }
        else
        {
            break;
        }
    }

    printf("\n");

    if (1 == is_empty_stack(&peg[popping_peg]))
    {
        printf("Peg empty, cannot pop. Try again.\n");
        goto choose_where_to_pop;
    }

    popping_value = stack_pop(&peg[popping_peg]);
    peg[popping_peg].stack[peg[popping_peg].top + 1] = 99;

    return popping_value;
}

void user_push(stack_t *peg, int item)
{
    int pushing_peg;

choose_where_to_push:

    while (1)
    {
        printf("Choose peg to push to: ");
        if (scanf("%d", &pushing_peg) < 1)
        {
            getchar();
            printf("You entered a non - numeric value, try again\n");
            continue;
        }

        if (pushing_peg > (NUM_PEGS - 1) || pushing_peg < 0)
        {
            printf("You entered a unvalid number, try again\n");
        }
        else
        {
            break;
        }
    }

    printf("\n");

    if (1 == is_empty_stack(&peg[pushing_peg]))
    {
        stack_push(&peg[pushing_peg], item);
    }
    else
    {
        if (stack_peek(&peg[pushing_peg]) > item)
        {
            stack_push(&peg[pushing_peg], item);
        }
        else
        {
            printf("Cannot push here. Try again.\n");
            goto choose_where_to_push;
        }
    }

    return;
}

int check_win_game(const stack_t *peg)
{
    for (int i = 1; i < NUM_PEGS; i++)
    {
        if (1 == is_full_stack(&peg[i]))
        {
            return 1;
        }
    }

    return 0;
}

void end_game(void)
{
    printf("Congratulations, you win!\n");

    return;
}