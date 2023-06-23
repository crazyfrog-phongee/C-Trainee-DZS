#include <stdio.h>
#include <stdlib.h> /* Need for functions such as malloc() */
#include <unistd.h> /* Need for functions such as brk(), sbrk() */

int a;

int main(int argc, char const *argv[])
{
    int *ptr;
    /* The current limit of the Heap is referred to as the program break */
    printf("Program break: %p\n", sbrk(0));
    ptr = sbrk(0) - 1;
    *ptr = 12;
    printf("%p\n", &a);

    /* Adjusts the program break by adding 4 to it */
    // sbrk(1);
    // printf("After adding 1, Program break: %p\n", sbrk(0));

    // ptr = sbrk(0) + 2;
    // *ptr = 10;
    // printf("Value of pointer: %p, %d\n", ptr, *ptr);

    return 0;
}
