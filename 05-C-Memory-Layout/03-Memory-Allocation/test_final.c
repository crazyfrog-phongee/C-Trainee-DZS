#include <stdio.h>
#include <stdlib.h>

void *int_init(int *x)
{
    x = (int *)malloc(sizeof(int));
    *x = 7;
    return x;
}

int main(void)
{
    int x = 10;
    free(int_init(&x));
    printf("X: %d\n", x);
    return 0;
}