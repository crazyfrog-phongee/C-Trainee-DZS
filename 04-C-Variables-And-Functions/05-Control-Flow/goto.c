#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i;
    for (i = 0; i < 10; i++)
    {
        if (i == 4)
            goto terminated_process;
        printf("%d ", i);
    }
terminated_process:
    printf("Terminate process\n");
    
    return 0;

}
