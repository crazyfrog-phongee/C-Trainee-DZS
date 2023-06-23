#include <stdio.h>

void show_mem_rep(char *start, int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf(" Address of 0x%.2x is %p \n", start[i], &start[i]);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int num = 0x11223344;
    show_mem_rep((char *) (&num), sizeof(num));
    return 0;
}
