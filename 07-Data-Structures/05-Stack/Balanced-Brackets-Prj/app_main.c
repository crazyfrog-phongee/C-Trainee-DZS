#include <stdio.h>
#include <string.h>

#include "stack_llist.h"

static llist_t *stack;
static llist_t *top1;
static llist_t *top2;
static llist_t *top3;

static int are_brackets_balanced(const char *str);

int main(int argc, char const *argv[])
{
    // stack = stack_create(stack);
    // char *str_test_1 = "{{([(())])}}";
    // char *str_test_2 = "(})";

    // if (0 == are_brackets_balanced(str_test_2))
    // {
    //     printf("Balanced\n");
    // }
    // else
    // {
    //     printf("Unbalanced\n");
    // }

    int i, j, k, a, b;
    int value = 0;

    top1 = stack_create(top1);
    top2 = stack_create(top2);
    top3 = stack_create(top3);

    printf("Enter number of disks:");
    scanf("%d", &i);

    for (j = 0; j < i; j++)
    {
        stack_push(top1, j);
    }

    printf("\n=====Before starting algorithm=====\n");
    print_stack(top1);
    print_stack(top2);
    print_stack(top3);

    printf("\n=====On starting algorithm=====\n");
    for (k = 1; k < 1 << i; k++)
    {
        a = (k & k - 1) % 3;
        b = ((k | k - 1) + 1) % 3;
        printf("Value of k = %d, a = %d, b = %d\n", k, a, b);

        switch (a)
        {
        case 0:
            value = stack_pop(top1);
            break;
        case 1:
            value = stack_pop(top2);
            break;
        case 2:
            value = stack_pop(top3);
            break;
        }

        switch (b)
        {
        case 0:
            stack_push(top1, value);
            break;
        case 1:
            stack_push(top2, value);
            break;
        case 2:
            stack_push(top3, value);
            break;
        }
        print_stack(top1);
        print_stack(top2);
        print_stack(top3);

        printf("\n\n\n");
    }

    stack_free(top1);
    stack_free(top2);
    stack_free(top3);
    
    return 0;
}

static int are_brackets_balanced(const char *str)
{

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[')
        {
            stack_push(stack, (int)str[i]);
            continue;
        }

        if (str[i] == ')' || str[i] == '}' || str[i] == ']')
        {
            if (0 == is_empty_stack(stack))
            {
                if (((char)stack_peek(stack) == '(' && str[i] == ')') || ((char)stack_peek(stack) == '[' && str[i] == ']') || ((char)stack_peek(stack) == '{' && str[i] == '}'))
                {
                    stack_pop(stack);
                }
                else
                {
                    break;
                }
            }
            else
            {
                return -1;
            }
        }
    }

    if (1 == is_empty_stack(stack))
    {
        return 0;
    }

    return -1;
}
