#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *test;

    test = (char *)calloc(15, sizeof(char));
    test = "DZS";
    printf("Hello %s\n", test);
    free(test);

    return 0;
}