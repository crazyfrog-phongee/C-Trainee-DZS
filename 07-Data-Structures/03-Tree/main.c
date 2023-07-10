#include <stdio.h>

int *func(int *ptr)
{
    int a = 5;
    *ptr = 10;
    ptr = &a;
}

int main(int argc, char const *argv[])
{
    int *ptr = malloc(sizeof(int));
    *ptr = 5;

    func(ptr);

    printf("%d", *ptr);
    return 0;
}
