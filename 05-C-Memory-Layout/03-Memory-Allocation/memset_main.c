#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int *test;

    test = (int *)malloc(15 * sizeof(int));
    memset(test, 0, sizeof(int) * 20);
    for (int i = 0; i < 15; i++)
    {
        printf("test[%d] after memset is %i\n", i, test[i]);

    }

    free(test);

    return 0;
}
